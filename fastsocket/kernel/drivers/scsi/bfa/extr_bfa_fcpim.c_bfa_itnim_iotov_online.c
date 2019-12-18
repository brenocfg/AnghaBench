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
struct bfa_itnim_s {int /*<<< orphan*/  io_q; int /*<<< orphan*/  pending_q; } ;
struct bfa_ioim_s {int /*<<< orphan*/  qe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  bfa_ioim_start (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_delayed_comp (struct bfa_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_itnim_iotov_stop (struct bfa_itnim_s*) ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_ioim_s**) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_itnim_iotov_online(struct bfa_itnim_s *itnim)
{
	struct bfa_ioim_s *ioim;

	bfa_itnim_iotov_stop(itnim);

	/*
	 * Abort all inflight IO requests in the queue
	 */
	bfa_itnim_delayed_comp(itnim, BFA_FALSE);

	/*
	 * Start all pending IO requests.
	 */
	while (!list_empty(&itnim->pending_q)) {
		bfa_q_deq(&itnim->pending_q, &ioim);
		list_add_tail(&ioim->qe, &itnim->io_q);
		bfa_ioim_start(ioim);
	}
}