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
struct mite_struct {scalar_t__ used; struct mite_struct* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  mite_device_id (struct mite_struct*) ; 
 struct mite_struct* mite_devices ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void mite_list_devices(void)
{
	struct mite_struct *mite, *next;

	printk("Available NI device IDs:");
	if (mite_devices)
		for (mite = mite_devices; mite; mite = next) {
			next = mite->next;
			printk(" 0x%04x", mite_device_id(mite));
			if (mite->used)
				printk("(used)");
		}
	printk("\n");

}