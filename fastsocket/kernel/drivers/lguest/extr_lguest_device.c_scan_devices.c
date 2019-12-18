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
struct lguest_device_desc {scalar_t__ type; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  add_lguest_device (struct lguest_device_desc*,unsigned int) ; 
 scalar_t__ desc_size (struct lguest_device_desc*) ; 
 struct lguest_device_desc* lguest_devices ; 
 int /*<<< orphan*/  printk (char*,unsigned int,scalar_t__) ; 

__attribute__((used)) static void scan_devices(void)
{
	unsigned int i;
	struct lguest_device_desc *d;

	/* We start at the page beginning, and skip over each entry. */
	for (i = 0; i < PAGE_SIZE; i += desc_size(d)) {
		d = lguest_devices + i;

		/* Once we hit a zero, stop. */
		if (d->type == 0)
			break;

		printk("Device at %i has size %u\n", i, desc_size(d));
		add_lguest_device(d, i);
	}
}