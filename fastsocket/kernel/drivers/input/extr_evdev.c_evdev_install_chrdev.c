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
struct evdev {size_t minor; } ;

/* Variables and functions */
 struct evdev** evdev_table ; 

__attribute__((used)) static int evdev_install_chrdev(struct evdev *evdev)
{
	/*
	 * No need to do any locking here as calls to connect and
	 * disconnect are serialized by the input core
	 */
	evdev_table[evdev->minor] = evdev;
	return 0;
}