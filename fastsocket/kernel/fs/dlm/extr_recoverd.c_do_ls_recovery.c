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
struct dlm_recover {scalar_t__ seq; struct dlm_recover* new; struct dlm_recover* nodeids; } ;
struct dlm_ls {scalar_t__ ls_recover_seq; int /*<<< orphan*/  ls_recover_lock; int /*<<< orphan*/  ls_flags; struct dlm_recover* ls_recover_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_RECOVERY_STOP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dlm_recover*) ; 
 int /*<<< orphan*/  ls_recover (struct dlm_ls*,struct dlm_recover*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_ls_recovery(struct dlm_ls *ls)
{
	struct dlm_recover *rv = NULL;

	spin_lock(&ls->ls_recover_lock);
	rv = ls->ls_recover_args;
	ls->ls_recover_args = NULL;
	if (rv && ls->ls_recover_seq == rv->seq)
		clear_bit(LSFL_RECOVERY_STOP, &ls->ls_flags);
	spin_unlock(&ls->ls_recover_lock);

	if (rv) {
		ls_recover(ls, rv);
		kfree(rv->nodeids);
		kfree(rv->new);
		kfree(rv);
	}
}