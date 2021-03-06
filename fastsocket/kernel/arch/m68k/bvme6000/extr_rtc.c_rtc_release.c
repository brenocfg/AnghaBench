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
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ rtc_status ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int rtc_release(struct inode *inode, struct file *file)
{
	lock_kernel();
	rtc_status = 0;
	unlock_kernel();
	return 0;
}