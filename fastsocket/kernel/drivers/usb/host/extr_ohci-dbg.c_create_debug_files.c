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
struct usb_bus {int /*<<< orphan*/  bus_name; } ;
struct ohci_hcd {int /*<<< orphan*/ * debug_dir; int /*<<< orphan*/ * debug_async; int /*<<< orphan*/ * debug_periodic; void* debug_registers; } ;
struct TYPE_2__ {struct usb_bus self; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debug_async_fops ; 
 int /*<<< orphan*/  debug_periodic_fops ; 
 int /*<<< orphan*/  debug_registers_fops ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_dbg (struct ohci_hcd*,char*) ; 
 int /*<<< orphan*/  ohci_debug_root ; 
 TYPE_1__* ohci_to_hcd (struct ohci_hcd*) ; 

__attribute__((used)) static inline void create_debug_files (struct ohci_hcd *ohci)
{
	struct usb_bus *bus = &ohci_to_hcd(ohci)->self;

	ohci->debug_dir = debugfs_create_dir(bus->bus_name, ohci_debug_root);
	if (!ohci->debug_dir)
		goto dir_error;

	ohci->debug_async = debugfs_create_file("async", S_IRUGO,
						ohci->debug_dir, ohci,
						&debug_async_fops);
	if (!ohci->debug_async)
		goto async_error;

	ohci->debug_periodic = debugfs_create_file("periodic", S_IRUGO,
						   ohci->debug_dir, ohci,
						   &debug_periodic_fops);
	if (!ohci->debug_periodic)
		goto periodic_error;

	ohci->debug_registers = debugfs_create_file("registers", S_IRUGO,
						    ohci->debug_dir, ohci,
						    &debug_registers_fops);
	if (!ohci->debug_registers)
		goto registers_error;

	ohci_dbg (ohci, "created debug files\n");
	return;

registers_error:
	debugfs_remove(ohci->debug_periodic);
periodic_error:
	debugfs_remove(ohci->debug_async);
async_error:
	debugfs_remove(ohci->debug_dir);
dir_error:
	ohci->debug_periodic = NULL;
	ohci->debug_async = NULL;
	ohci->debug_dir = NULL;
}