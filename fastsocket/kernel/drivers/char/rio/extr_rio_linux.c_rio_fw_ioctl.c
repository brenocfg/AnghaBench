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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  p ; 
 int riocontrol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static long rio_fw_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int rc = 0;
	func_enter();

	/* The "dev" argument isn't used. */
	lock_kernel();
	rc = riocontrol(p, 0, cmd, arg, capable(CAP_SYS_ADMIN));
	unlock_kernel();

	func_exit();
	return rc;
}