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
struct tty_dev_t {int (* name ) (int /*<<< orphan*/ ,char*,size_t) ;} ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 struct tty_dev_t* pty_get_driver (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
pty_get_name(dev_t dev, char *buffer, size_t size)
{
	struct tty_dev_t *driver = pty_get_driver(dev);
	if (driver && driver->name) {
		return driver->name(minor(dev), buffer, size);
	}
	return 0;
}