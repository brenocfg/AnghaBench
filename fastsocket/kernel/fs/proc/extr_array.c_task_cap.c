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
struct seq_file {int dummy; } ;
struct cred {int /*<<< orphan*/  cap_bset; int /*<<< orphan*/  cap_effective; int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_inheritable; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  render_cap_t (struct seq_file*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void task_cap(struct seq_file *m, struct task_struct *p)
{
	const struct cred *cred;
	kernel_cap_t cap_inheritable, cap_permitted, cap_effective, cap_bset;

	rcu_read_lock();
	cred = __task_cred(p);
	cap_inheritable	= cred->cap_inheritable;
	cap_permitted	= cred->cap_permitted;
	cap_effective	= cred->cap_effective;
	cap_bset	= cred->cap_bset;
	rcu_read_unlock();

	render_cap_t(m, "CapInh:\t", &cap_inheritable);
	render_cap_t(m, "CapPrm:\t", &cap_permitted);
	render_cap_t(m, "CapEff:\t", &cap_effective);
	render_cap_t(m, "CapBnd:\t", &cap_bset);
}