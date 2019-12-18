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
struct fown_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGURG ; 
 int /*<<< orphan*/  do_send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,int) ; 
 scalar_t__ sigio_perm (struct task_struct*,struct fown_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_sigurg_to_task(struct task_struct *p,
				struct fown_struct *fown, int group)
{
	if (sigio_perm(p, fown, SIGURG))
		do_send_sig_info(SIGURG, SEND_SIG_PRIV, p, group);
}