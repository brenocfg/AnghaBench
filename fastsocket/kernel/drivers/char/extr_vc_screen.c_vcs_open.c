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
 int ENXIO ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  vc_cons_allocated (unsigned int) ; 

__attribute__((used)) static int
vcs_open(struct inode *inode, struct file *filp)
{
	unsigned int currcons = iminor(inode) & 127;
	int ret = 0;
	
	lock_kernel();
	if(currcons && !vc_cons_allocated(currcons-1))
		ret = -ENXIO;
	unlock_kernel();
	return ret;
}