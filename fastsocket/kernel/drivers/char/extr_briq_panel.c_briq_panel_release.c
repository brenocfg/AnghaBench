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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ vfd_is_open ; 

__attribute__((used)) static int briq_panel_release(struct inode *ino, struct file *filep)
{
	if (!vfd_is_open)
		return -ENODEV;

	vfd_is_open = 0;

	return 0;
}