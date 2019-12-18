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
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  u8 ;
struct pci_controller {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
xilinx_pci_exclude_device(struct pci_controller *hose, u_char bus, u8 devfn)
{
	return (bus != 0);
}