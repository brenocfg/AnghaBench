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
 int /*<<< orphan*/  global_driver ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  uctrl_get_event_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uctrl_get_external_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
uctrl_open(struct inode *inode, struct file *file)
{
	lock_kernel();
	uctrl_get_event_status(global_driver);
	uctrl_get_external_status(global_driver);
	unlock_kernel();
	return 0;
}