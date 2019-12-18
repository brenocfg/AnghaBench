#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qla_hw_data {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct nvram_24xx {int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 

__attribute__((used)) static void qla24xx_nvram_wwn_from_ofw(scsi_qla_host_t *vha,
	struct nvram_24xx *nv)
{
#ifdef CONFIG_SPARC
	struct qla_hw_data *ha = vha->hw;
	struct pci_dev *pdev = ha->pdev;
	struct device_node *dp = pci_device_to_OF_node(pdev);
	const u8 *val;
	int len;

	val = of_get_property(dp, "port-wwn", &len);
	if (val && len >= WWN_SIZE)
		memcpy(nv->port_name, val, WWN_SIZE);

	val = of_get_property(dp, "node-wwn", &len);
	if (val && len >= WWN_SIZE)
		memcpy(nv->node_name, val, WWN_SIZE);
#endif
}