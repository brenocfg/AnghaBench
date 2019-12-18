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
struct i7core_pvt {int /*<<< orphan*/ * i7core_pci; TYPE_1__* i7core_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  edac_pci_release_generic_ctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i7core_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i7core_pci_ctl_release(struct i7core_pvt *pvt)
{
	if (likely(pvt->i7core_pci))
		edac_pci_release_generic_ctl(pvt->i7core_pci);
	else
		i7core_printk(KERN_ERR,
				"Couldn't find mem_ctl_info for socket %d\n",
				pvt->i7core_dev->socket);
	pvt->i7core_pci = NULL;
}