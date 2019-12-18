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
typedef  int /*<<< orphan*/  u16 ;
struct task_struct {int dummy; } ;
struct kern_ipc_perm {struct ipc_security_struct* security; } ;
struct ipc_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ipc_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int ipc_alloc_security(struct task_struct *task,
			      struct kern_ipc_perm *perm,
			      u16 sclass)
{
	struct ipc_security_struct *isec;
	u32 sid;

	isec = kzalloc(sizeof(struct ipc_security_struct), GFP_KERNEL);
	if (!isec)
		return -ENOMEM;

	sid = task_sid(task);
	isec->sclass = sclass;
	isec->sid = sid;
	perm->security = isec;

	return 0;
}