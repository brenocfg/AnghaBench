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
struct fc_seq {int dummy; } ;
struct fc_exch {int /*<<< orphan*/  ex_lock; } ;

/* Variables and functions */
 int fc_exch_abort_locked (struct fc_exch*,unsigned int) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_seq_exch_abort(const struct fc_seq *req_sp,
			     unsigned int timer_msec)
{
	struct fc_exch *ep;
	int error;

	ep = fc_seq_exch(req_sp);
	spin_lock_bh(&ep->ex_lock);
	error = fc_exch_abort_locked(ep, timer_msec);
	spin_unlock_bh(&ep->ex_lock);
	return error;
}