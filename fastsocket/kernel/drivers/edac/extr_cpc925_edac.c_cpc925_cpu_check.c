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
typedef  int u32 ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; struct cpc925_dev_info* pvt_info; } ;
struct cpc925_dev_info {scalar_t__ vbase; } ;

/* Variables and functions */
 int CPU_EXCP_DETECTED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ REG_APIEXCP_OFFSET ; 
 scalar_t__ REG_APIMASK_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  cpc925_printk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpc925_cpu_check(struct edac_device_ctl_info *edac_dev)
{
	struct cpc925_dev_info *dev_info = edac_dev->pvt_info;
	u32 apiexcp;
	u32 apimask;

	/* APIEXCP is cleared when read */
	apiexcp = __raw_readl(dev_info->vbase + REG_APIEXCP_OFFSET);
	if ((apiexcp & CPU_EXCP_DETECTED) == 0)
		return;

	apimask = __raw_readl(dev_info->vbase + REG_APIMASK_OFFSET);
	cpc925_printk(KERN_INFO, "Processor Interface Fault\n"
				 "Processor Interface register dump:\n");
	cpc925_printk(KERN_INFO, "APIMASK		0x%08x\n", apimask);
	cpc925_printk(KERN_INFO, "APIEXCP		0x%08x\n", apiexcp);

	edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
}