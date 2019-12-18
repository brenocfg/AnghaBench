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

/* Variables and functions */
 int /*<<< orphan*/  b44_pci_driver ; 
 int ssb_pcihost_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int b44_pci_init(void)
{
	int err = 0;
#ifdef CONFIG_B44_PCI
	err = ssb_pcihost_register(&b44_pci_driver);
#endif
	return err;
}