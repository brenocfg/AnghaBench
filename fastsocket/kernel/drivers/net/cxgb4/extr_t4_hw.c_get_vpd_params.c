#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vpd ;
typedef  scalar_t__ u8 ;
struct vpd_params {int /*<<< orphan*/  sn; int /*<<< orphan*/  ec; int /*<<< orphan*/  id; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 unsigned int EC_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIND_VPD_KW (int,char*) ; 
 unsigned int ID_LEN ; 
 int PCI_VPD_INFO_FLD_HDR_SIZE ; 
 scalar_t__ PCI_VPD_LRDT_ID_STRING ; 
 int /*<<< orphan*/  PCI_VPD_LRDT_RO_DATA ; 
 int PCI_VPD_LRDT_TAG_SIZE ; 
 int /*<<< orphan*/  SERNUM_LEN ; 
 int /*<<< orphan*/  VPD_BASE ; 
 int VPD_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,unsigned int) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_vpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int pci_vpd_find_tag (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pci_vpd_info_field_size (scalar_t__*) ; 
 unsigned int pci_vpd_lrdt_size (scalar_t__*) ; 
 int /*<<< orphan*/  strim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vpd_params(struct adapter *adapter, struct vpd_params *p)
{
	int i, ret;
	int ec, sn;
	u8 vpd[VPD_LEN], csum;
	unsigned int vpdr_len, kw_offset, id_len;

	ret = pci_read_vpd(adapter->pdev, VPD_BASE, sizeof(vpd), vpd);
	if (ret < 0)
		return ret;

	if (vpd[0] != PCI_VPD_LRDT_ID_STRING) {
		dev_err(adapter->pdev_dev, "missing VPD ID string\n");
		return -EINVAL;
	}

	id_len = pci_vpd_lrdt_size(vpd);
	if (id_len > ID_LEN)
		id_len = ID_LEN;

	i = pci_vpd_find_tag(vpd, 0, VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	if (i < 0) {
		dev_err(adapter->pdev_dev, "missing VPD-R section\n");
		return -EINVAL;
	}

	vpdr_len = pci_vpd_lrdt_size(&vpd[i]);
	kw_offset = i + PCI_VPD_LRDT_TAG_SIZE;
	if (vpdr_len + kw_offset > VPD_LEN) {
		dev_err(adapter->pdev_dev, "bad VPD-R length %u\n", vpdr_len);
		return -EINVAL;
	}

#define FIND_VPD_KW(var, name) do { \
	var = pci_vpd_find_info_keyword(vpd, kw_offset, vpdr_len, name); \
	if (var < 0) { \
		dev_err(adapter->pdev_dev, "missing VPD keyword " name "\n"); \
		return -EINVAL; \
	} \
	var += PCI_VPD_INFO_FLD_HDR_SIZE; \
} while (0)

	FIND_VPD_KW(i, "RV");
	for (csum = 0; i >= 0; i--)
		csum += vpd[i];

	if (csum) {
		dev_err(adapter->pdev_dev,
			"corrupted VPD EEPROM, actual csum %u\n", csum);
		return -EINVAL;
	}

	FIND_VPD_KW(ec, "EC");
	FIND_VPD_KW(sn, "SN");
#undef FIND_VPD_KW

	memcpy(p->id, vpd + PCI_VPD_LRDT_TAG_SIZE, id_len);
	strim(p->id);
	memcpy(p->ec, vpd + ec, EC_LEN);
	strim(p->ec);
	i = pci_vpd_info_field_size(vpd + sn - PCI_VPD_INFO_FLD_HDR_SIZE);
	memcpy(p->sn, vpd + sn, min(i, SERNUM_LEN));
	strim(p->sn);
	return 0;
}