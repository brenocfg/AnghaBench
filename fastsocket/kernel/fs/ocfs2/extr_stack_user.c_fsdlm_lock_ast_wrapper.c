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
struct dlm_lksb {int sb_status; } ;
struct TYPE_4__ {TYPE_1__* sp_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lp_lock_ast ) (void*) ;int /*<<< orphan*/  (* lp_unlock_ast ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int DLM_ECANCEL ; 
 int DLM_EUNLOCK ; 
 struct dlm_lksb* fsdlm_astarg_to_lksb (void*) ; 
 TYPE_2__ ocfs2_user_plugin ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void fsdlm_lock_ast_wrapper(void *astarg)
{
	struct dlm_lksb *lksb = fsdlm_astarg_to_lksb(astarg);
	int status = lksb->sb_status;

	BUG_ON(ocfs2_user_plugin.sp_proto == NULL);

	/*
	 * For now we're punting on the issue of other non-standard errors
	 * where we can't tell if the unlock_ast or lock_ast should be called.
	 * The main "other error" that's possible is EINVAL which means the
	 * function was called with invalid args, which shouldn't be possible
	 * since the caller here is under our control.  Other non-standard
	 * errors probably fall into the same category, or otherwise are fatal
	 * which means we can't carry on anyway.
	 */

	if (status == -DLM_EUNLOCK || status == -DLM_ECANCEL)
		ocfs2_user_plugin.sp_proto->lp_unlock_ast(astarg, 0);
	else
		ocfs2_user_plugin.sp_proto->lp_lock_ast(astarg);
}