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
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;
struct TYPE_4__ {TYPE_1__* sp_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lp_unlock_ast ) (void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int DLM_CANCELGRANT ; 
 int dlm_status_to_errno (int) ; 
 TYPE_2__ o2cb_stack ; 
 int /*<<< orphan*/  stub1 (void*,int) ; 

__attribute__((used)) static void o2dlm_unlock_ast_wrapper(void *astarg, enum dlm_status status)
{
	int error = dlm_status_to_errno(status);

	BUG_ON(o2cb_stack.sp_proto == NULL);

	/*
	 * In o2dlm, you can get both the lock_ast() for the lock being
	 * granted and the unlock_ast() for the CANCEL failing.  A
	 * successful cancel sends DLM_NORMAL here.  If the
	 * lock grant happened before the cancel arrived, you get
	 * DLM_CANCELGRANT.
	 *
	 * There's no need for the double-ast.  If we see DLM_CANCELGRANT,
	 * we just ignore it.  We expect the lock_ast() to handle the
	 * granted lock.
	 */
	if (status == DLM_CANCELGRANT)
		return;

	o2cb_stack.sp_proto->lp_unlock_ast(astarg, error);
}