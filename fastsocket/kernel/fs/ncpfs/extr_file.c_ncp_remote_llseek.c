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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  generic_file_llseek_unlocked (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static loff_t ncp_remote_llseek(struct file *file, loff_t offset, int origin)
{
	loff_t ret;
	lock_kernel();
	ret = generic_file_llseek_unlocked(file, offset, origin);
	unlock_kernel();
	return ret;
}