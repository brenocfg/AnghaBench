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
struct file {int f_flags; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int O_WRONLY ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  policy_opencount ; 

int ima_open_policy(struct inode * inode, struct file * filp)
{
	/* No point in being allowed to open it if you aren't going to write */
	if (!(filp->f_flags & O_WRONLY))
		return -EACCES;
	if (atomic_dec_and_test(&policy_opencount))
		return 0;
	return -EBUSY;
}