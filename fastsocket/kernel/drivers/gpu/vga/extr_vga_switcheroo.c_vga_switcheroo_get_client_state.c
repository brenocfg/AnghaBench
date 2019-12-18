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
struct vga_switcheroo_client {int pwr_state; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int VGA_SWITCHEROO_INIT ; 
 int VGA_SWITCHEROO_NOT_FOUND ; 
 struct vga_switcheroo_client* find_client_from_pci (int /*<<< orphan*/ *,struct pci_dev*) ; 
 TYPE_1__ vgasr_priv ; 

int vga_switcheroo_get_client_state(struct pci_dev *pdev)
{
	struct vga_switcheroo_client *client;

	client = find_client_from_pci(&vgasr_priv.clients, pdev);
	if (!client)
		return VGA_SWITCHEROO_NOT_FOUND;
	if (!vgasr_priv.active)
		return VGA_SWITCHEROO_INIT;
	return client->pwr_state;
}