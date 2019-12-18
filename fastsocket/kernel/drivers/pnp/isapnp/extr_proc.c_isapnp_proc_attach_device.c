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
struct proc_dir_entry {int size; } ;
struct pnp_dev {int number; struct proc_dir_entry* procent; struct pnp_card* card; } ;
struct pnp_card {int number; struct proc_dir_entry* procdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  isapnp_proc_bus_dir ; 
 int /*<<< orphan*/  isapnp_proc_bus_file_operations ; 
 struct proc_dir_entry* proc_create_data (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ *,struct pnp_dev*) ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int isapnp_proc_attach_device(struct pnp_dev *dev)
{
	struct pnp_card *bus = dev->card;
	struct proc_dir_entry *de, *e;
	char name[16];

	if (!(de = bus->procdir)) {
		sprintf(name, "%02x", bus->number);
		de = bus->procdir = proc_mkdir(name, isapnp_proc_bus_dir);
		if (!de)
			return -ENOMEM;
	}
	sprintf(name, "%02x", dev->number);
	e = dev->procent = proc_create_data(name, S_IFREG | S_IRUGO, de,
			&isapnp_proc_bus_file_operations, dev);
	if (!e)
		return -ENOMEM;
	e->size = 256;
	return 0;
}