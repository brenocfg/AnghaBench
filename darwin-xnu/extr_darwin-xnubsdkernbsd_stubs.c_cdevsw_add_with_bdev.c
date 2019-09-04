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
struct cdevsw {int dummy; } ;

/* Variables and functions */
 scalar_t__ cdev_set_bdev (int,int) ; 
 int cdevsw_add (int,struct cdevsw*) ; 
 int /*<<< orphan*/  cdevsw_remove (int,struct cdevsw*) ; 

int
cdevsw_add_with_bdev(int index, struct cdevsw * csw, int bdev)
{
	index = cdevsw_add(index, csw);
	if (index < 0) {
		return (index);
	}
	if (cdev_set_bdev(index, bdev) < 0) {
		cdevsw_remove(index, csw);
		return (-1);
	}
	return (index);
}