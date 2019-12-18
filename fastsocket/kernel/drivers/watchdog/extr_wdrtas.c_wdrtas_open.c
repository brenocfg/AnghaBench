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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  wdrtas_miscdev_open ; 
 int /*<<< orphan*/  wdrtas_timer_keepalive () ; 
 int /*<<< orphan*/  wdrtas_timer_start () ; 

__attribute__((used)) static int wdrtas_open(struct inode *inode, struct file *file)
{
	/* only open once */
	if (atomic_inc_return(&wdrtas_miscdev_open) > 1) {
		atomic_dec(&wdrtas_miscdev_open);
		return -EBUSY;
	}

	wdrtas_timer_start();
	wdrtas_timer_keepalive();

	return nonseekable_open(inode, file);
}