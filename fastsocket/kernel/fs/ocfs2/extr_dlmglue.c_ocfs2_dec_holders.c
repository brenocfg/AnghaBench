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
struct ocfs2_lock_res {int /*<<< orphan*/  l_ro_holders; int /*<<< orphan*/  l_ex_holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 

__attribute__((used)) static inline void ocfs2_dec_holders(struct ocfs2_lock_res *lockres,
				     int level)
{
	mlog_entry_void();

	BUG_ON(!lockres);

	switch(level) {
	case DLM_LOCK_EX:
		BUG_ON(!lockres->l_ex_holders);
		lockres->l_ex_holders--;
		break;
	case DLM_LOCK_PR:
		BUG_ON(!lockres->l_ro_holders);
		lockres->l_ro_holders--;
		break;
	default:
		BUG();
	}
	mlog_exit_void();
}