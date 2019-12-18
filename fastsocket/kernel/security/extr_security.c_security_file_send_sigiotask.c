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
struct fown_struct {int dummy; } ;
struct TYPE_2__ {int (* file_send_sigiotask ) (struct task_struct*,struct fown_struct*,int) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct task_struct*,struct fown_struct*,int) ; 

int security_file_send_sigiotask(struct task_struct *tsk,
				  struct fown_struct *fown, int sig)
{
	return security_ops->file_send_sigiotask(tsk, fown, sig);
}