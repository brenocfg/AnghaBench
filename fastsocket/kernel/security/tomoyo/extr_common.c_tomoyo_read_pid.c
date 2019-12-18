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
struct tomoyo_io_buffer {scalar_t__ read_avail; int read_eof; int read_step; } ;
struct tomoyo_domain_info {TYPE_1__* domainname; int /*<<< orphan*/  profile; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct task_struct* find_task_by_vpid (int const) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tomoyo_domain_info* tomoyo_real_domain (struct task_struct*) ; 

__attribute__((used)) static int tomoyo_read_pid(struct tomoyo_io_buffer *head)
{
	if (head->read_avail == 0 && !head->read_eof) {
		const int pid = head->read_step;
		struct task_struct *p;
		struct tomoyo_domain_info *domain = NULL;
		read_lock(&tasklist_lock);
		p = find_task_by_vpid(pid);
		if (p)
			domain = tomoyo_real_domain(p);
		read_unlock(&tasklist_lock);
		if (domain)
			tomoyo_io_printf(head, "%d %u %s", pid, domain->profile,
					 domain->domainname->name);
		head->read_eof = true;
	}
	return 0;
}