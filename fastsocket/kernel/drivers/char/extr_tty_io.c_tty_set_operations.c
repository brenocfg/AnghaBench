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
struct tty_operations {int dummy; } ;
struct tty_driver {struct tty_operations const* ops; } ;

/* Variables and functions */

void tty_set_operations(struct tty_driver *driver,
			const struct tty_operations *op)
{
	driver->ops = op;
}