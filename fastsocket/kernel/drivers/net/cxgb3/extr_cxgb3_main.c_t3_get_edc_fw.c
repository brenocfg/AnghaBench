#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct firmware {int size; scalar_t__ data; } ;
struct cphy {int /*<<< orphan*/ * phy_cache; struct adapter* adapter; } ;
struct adapter {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  csum ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,int,...) ; 
 int EINVAL ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 char* get_edc_fw_name (int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

int t3_get_edc_fw(struct cphy *phy, int edc_idx, int size)
{
	struct adapter *adapter = phy->adapter;
	const struct firmware *fw;
	char buf[64];
	u32 csum;
	const __be32 *p;
	u16 *cache = phy->phy_cache;
	int i, ret;

	snprintf(buf, sizeof(buf), get_edc_fw_name(edc_idx));

	ret = request_firmware(&fw, buf, &adapter->pdev->dev);
	if (ret < 0) {
		dev_err(&adapter->pdev->dev,
			"could not upgrade firmware: unable to load %s\n",
			buf);
		return ret;
	}

	/* check size, take checksum in account */
	if (fw->size > size + 4) {
		CH_ERR(adapter, "firmware image too large %u, expected %d\n",
		       (unsigned int)fw->size, size + 4);
		ret = -EINVAL;
	}

	/* compute checksum */
	p = (const __be32 *)fw->data;
	for (csum = 0, i = 0; i < fw->size / sizeof(csum); i++)
		csum += ntohl(p[i]);

	if (csum != 0xffffffff) {
		CH_ERR(adapter, "corrupted firmware image, checksum %u\n",
		       csum);
		ret = -EINVAL;
	}

	for (i = 0; i < size / 4 ; i++) {
		*cache++ = (be32_to_cpu(p[i]) & 0xffff0000) >> 16;
		*cache++ = be32_to_cpu(p[i]) & 0xffff;
	}

	release_firmware(fw);

	return ret;
}