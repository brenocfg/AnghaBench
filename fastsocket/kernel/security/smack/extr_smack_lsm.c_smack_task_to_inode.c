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
struct task_struct {int dummy; } ;
struct inode_smack {int /*<<< orphan*/  smk_inode; } ;
struct inode {struct inode_smack* i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  task_security (struct task_struct*) ; 

__attribute__((used)) static void smack_task_to_inode(struct task_struct *p, struct inode *inode)
{
	struct inode_smack *isp = inode->i_security;
	isp->smk_inode = task_security(p);
}