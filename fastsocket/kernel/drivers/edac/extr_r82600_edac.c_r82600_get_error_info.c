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
struct r82600_error_info {int eapr; } ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  R82600_EAP ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_bits32 (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r82600_get_error_info(struct mem_ctl_info *mci,
				struct r82600_error_info *info)
{
	struct pci_dev *pdev;

	pdev = to_pci_dev(mci->dev);
	pci_read_config_dword(pdev, R82600_EAP, &info->eapr);

	if (info->eapr & BIT(0))
		/* Clear error to allow next error to be reported [p.62] */
		pci_write_bits32(pdev, R82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));

	if (info->eapr & BIT(1))
		/* Clear error to allow next error to be reported [p.62] */
		pci_write_bits32(pdev, R82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));
}