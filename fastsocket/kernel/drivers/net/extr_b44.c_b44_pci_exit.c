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
 int /*<<< orphan*/  ssb_pcihost_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void b44_pci_exit(void)
{
#ifdef CONFIG_B44_PCI
	ssb_pcihost_unregister(&b44_pci_driver);
#endif
}