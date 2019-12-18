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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct inode_security_struct {int initialized; int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static void selinux_task_to_inode(struct task_struct *p,
				  struct inode *inode)
{
	struct inode_security_struct *isec = inode->i_security;
	u32 sid = task_sid(p);

	isec->sid = sid;
	isec->initialized = 1;
}