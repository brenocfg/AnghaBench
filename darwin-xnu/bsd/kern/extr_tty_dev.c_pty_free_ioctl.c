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
struct tty_dev_t {int (* free ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 struct tty_dev_t* pty_get_driver (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pty_free_ioctl(dev_t dev, int open_flag)
{
	struct tty_dev_t *driver = pty_get_driver(dev);
	if (driver && driver->free) {
		return driver->free(minor(dev), open_flag);
	}
	return 0;
}