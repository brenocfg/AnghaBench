#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {int /*<<< orphan*/  mm; int /*<<< orphan*/  envc; int /*<<< orphan*/  argc; } ;
struct audit_context {void* aux; scalar_t__ dummy; } ;
struct TYPE_3__ {void* next; int /*<<< orphan*/  type; } ;
struct audit_aux_data_execve {TYPE_1__ d; int /*<<< orphan*/  mm; int /*<<< orphan*/  envc; int /*<<< orphan*/  argc; } ;
struct TYPE_4__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_EXECVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_enabled ; 
 TYPE_2__* current ; 
 struct audit_aux_data_execve* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

int audit_bprm(struct linux_binprm *bprm)
{
	struct audit_aux_data_execve *ax;
	struct audit_context *context = current->audit_context;

	if (likely(!audit_enabled || !context || context->dummy))
		return 0;

	ax = kmalloc(sizeof(*ax), GFP_KERNEL);
	if (!ax)
		return -ENOMEM;

	ax->argc = bprm->argc;
	ax->envc = bprm->envc;
	ax->mm = bprm->mm;
	ax->d.type = AUDIT_EXECVE;
	ax->d.next = context->aux;
	context->aux = (void *)ax;
	return 0;
}