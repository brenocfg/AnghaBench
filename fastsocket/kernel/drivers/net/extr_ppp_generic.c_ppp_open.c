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
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cycle_kernel_lock () ; 

__attribute__((used)) static int ppp_open(struct inode *inode, struct file *file)
{
	cycle_kernel_lock();
	/*
	 * This could (should?) be enforced by the permissions on /dev/ppp.
	 */
	if (!capable(CAP_NET_ADMIN))
		return -EPERM;
	return 0;
}