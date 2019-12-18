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
struct proc_dir_entry {void* data; void* write_proc; void* read_proc; } ;
struct pnp_bios_node {int handle; } ;

/* Variables and functions */
 int EIO ; 
 struct proc_dir_entry* create_proc_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnpbios_dont_use_current_config ; 
 int /*<<< orphan*/  proc_pnp ; 
 int /*<<< orphan*/  proc_pnp_boot ; 
 void* proc_read_node ; 
 void* proc_write_node ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int pnpbios_interface_attach_device(struct pnp_bios_node *node)
{
	char name[3];
	struct proc_dir_entry *ent;

	sprintf(name, "%02x", node->handle);

	if (!proc_pnp)
		return -EIO;
	if (!pnpbios_dont_use_current_config) {
		ent = create_proc_entry(name, 0, proc_pnp);
		if (ent) {
			ent->read_proc = proc_read_node;
			ent->write_proc = proc_write_node;
			ent->data = (void *)(long)(node->handle);
		}
	}

	if (!proc_pnp_boot)
		return -EIO;
	ent = create_proc_entry(name, 0, proc_pnp_boot);
	if (ent) {
		ent->read_proc = proc_read_node;
		ent->write_proc = proc_write_node;
		ent->data = (void *)(long)(node->handle + 0x100);
		return 0;
	}

	return -EIO;
}