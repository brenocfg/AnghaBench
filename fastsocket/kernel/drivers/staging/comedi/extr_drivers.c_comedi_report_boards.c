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
struct comedi_driver {char const* const driver_name; char** board_name; unsigned int num_names; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,char const* const) ; 

void comedi_report_boards(struct comedi_driver *driv)
{
	unsigned int i;
	const char *const *name_ptr;

	printk("comedi: valid board names for %s driver are:\n",
	       driv->driver_name);

	name_ptr = driv->board_name;
	for (i = 0; i < driv->num_names; i++) {
		printk(" %s\n", *name_ptr);
		name_ptr = (const char **)((char *)name_ptr + driv->offset);
	}

	if (driv->num_names == 0)
		printk(" %s\n", driv->driver_name);
}