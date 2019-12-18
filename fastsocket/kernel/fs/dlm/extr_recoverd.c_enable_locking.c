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
typedef  scalar_t__ uint64_t ;
struct dlm_ls {scalar_t__ ls_recover_seq; int /*<<< orphan*/  ls_recv_active; int /*<<< orphan*/  ls_recover_lock; int /*<<< orphan*/  ls_in_recovery; int /*<<< orphan*/  ls_flags; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  LSFL_RUNNING ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enable_locking(struct dlm_ls *ls, uint64_t seq)
{
	int error = -EINTR;

	down_write(&ls->ls_recv_active);

	spin_lock(&ls->ls_recover_lock);
	if (ls->ls_recover_seq == seq) {
		set_bit(LSFL_RUNNING, &ls->ls_flags);
		/* unblocks processes waiting to enter the dlm */
		up_write(&ls->ls_in_recovery);
		error = 0;
	}
	spin_unlock(&ls->ls_recover_lock);

	up_write(&ls->ls_recv_active);
	return error;
}