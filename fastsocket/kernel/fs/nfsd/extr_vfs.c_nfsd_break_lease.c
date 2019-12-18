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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int break_lease (struct inode*,int) ; 

__attribute__((used)) static int nfsd_break_lease(struct inode *inode)
{
	if (!S_ISREG(inode->i_mode))
		return 0;
	return break_lease(inode, O_WRONLY | O_NONBLOCK);
}