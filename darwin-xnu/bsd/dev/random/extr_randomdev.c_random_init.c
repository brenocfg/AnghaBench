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

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_CHAR ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  RANDOM_MAJOR ; 
 int /*<<< orphan*/  RANDOM_MINOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  URANDOM_MINOR ; 
 int cdevsw_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfs_make_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makedev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  random_cdevsw ; 

void
random_init(void)
{
	int ret;

	ret = cdevsw_add(RANDOM_MAJOR, &random_cdevsw);
	if (ret < 0) {
		panic("random_init: failed to allocate a major number!");
	}

	devfs_make_node(makedev (ret, RANDOM_MINOR), DEVFS_CHAR,
		UID_ROOT, GID_WHEEL, 0666, "random", 0);

	/*
	 * also make urandom
	 * (which is exactly the same thing in our context)
	 */
	devfs_make_node(makedev (ret, URANDOM_MINOR), DEVFS_CHAR,
		UID_ROOT, GID_WHEEL, 0666, "urandom", 0);

}