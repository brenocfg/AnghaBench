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
typedef  int /*<<< orphan*/  u8 ;
struct pnp_bios_node {int dummy; } ;

/* Variables and functions */
 int __pnp_bios_set_dev_node (int /*<<< orphan*/ ,char,struct pnp_bios_node*) ; 
 int pnp_bios_get_dev_node (int /*<<< orphan*/ *,char,struct pnp_bios_node*) ; 
 int /*<<< orphan*/  pnpbios_print_status (char*,int) ; 

int pnp_bios_set_dev_node(u8 nodenum, char boot, struct pnp_bios_node *data)
{
	int status;

	status = __pnp_bios_set_dev_node(nodenum, boot, data);
	if (status) {
		pnpbios_print_status("set_dev_node", status);
		return status;
	}
	if (!boot) {		/* Update devlist */
		status = pnp_bios_get_dev_node(&nodenum, boot, data);
		if (status)
			return status;
	}
	return status;
}