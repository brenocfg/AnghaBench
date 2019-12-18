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
struct fown_struct {scalar_t__ euid; scalar_t__ uid; } ;
struct cred {scalar_t__ suid; scalar_t__ uid; } ;

/* Variables and functions */
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  security_file_send_sigiotask (struct task_struct*,struct fown_struct*,int) ; 

__attribute__((used)) static inline int sigio_perm(struct task_struct *p,
                             struct fown_struct *fown, int sig)
{
	const struct cred *cred;
	int ret;

	rcu_read_lock();
	cred = __task_cred(p);
	ret = ((fown->euid == 0 ||
		fown->euid == cred->suid || fown->euid == cred->uid ||
		fown->uid  == cred->suid || fown->uid  == cred->uid) &&
	       !security_file_send_sigiotask(p, fown, sig));
	rcu_read_unlock();
	return ret;
}