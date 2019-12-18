#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* task_to_inode ) (struct task_struct*,struct inode*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct task_struct*,struct inode*) ; 

void security_task_to_inode(struct task_struct *p, struct inode *inode)
{
	security_ops->task_to_inode(p, inode);
}