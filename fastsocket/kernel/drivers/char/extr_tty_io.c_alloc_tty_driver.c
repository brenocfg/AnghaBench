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
struct tty_driver {int num; int /*<<< orphan*/  magic; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TTY_DRIVER_MAGIC ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct tty_driver* kzalloc (int,int /*<<< orphan*/ ) ; 

struct tty_driver *alloc_tty_driver(int lines)
{
	struct tty_driver *driver;

	driver = kzalloc(sizeof(struct tty_driver), GFP_KERNEL);
	if (driver) {
		kref_init(&driver->kref);
		driver->magic = TTY_DRIVER_MAGIC;
		driver->num = lines;
		/* later we'll move allocation of tables here */
	}
	return driver;
}