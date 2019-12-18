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
struct task_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  osid; } ;
struct cred {struct task_security_struct* security; } ;
struct TYPE_2__ {scalar_t__ real_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
 TYPE_1__* current ; 
 struct task_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void cred_init_security(void)
{
	struct cred *cred = (struct cred *) current->real_cred;
	struct task_security_struct *tsec;

	tsec = kzalloc(sizeof(struct task_security_struct), GFP_KERNEL);
	if (!tsec)
		panic("SELinux:  Failed to initialize initial task.\n");

	tsec->osid = tsec->sid = SECINITSID_KERNEL;
	cred->security = tsec;
}