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
 int EBUSY ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int perf_enabled ; 
 int /*<<< orphan*/  perf_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int perf_open(struct inode *inode, struct file *file)
{
	lock_kernel();
	spin_lock(&perf_lock);
	if (perf_enabled) {
		spin_unlock(&perf_lock);
		unlock_kernel();
		return -EBUSY;
	}
	perf_enabled = 1;
 	spin_unlock(&perf_lock);
	unlock_kernel();

	return 0;
}