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
struct task_security_struct {int dummy; } ;
struct cred {struct task_security_struct* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct task_security_struct*) ; 

__attribute__((used)) static void selinux_cred_free(struct cred *cred)
{
	struct task_security_struct *tsec = cred->security;

	BUG_ON((unsigned long) cred->security < PAGE_SIZE);
	cred->security = (void *) 0x7UL;
	kfree(tsec);
}