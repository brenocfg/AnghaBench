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
struct srp_target_port {int /*<<< orphan*/  free_tx; } ;
struct srp_iu {int /*<<< orphan*/  list; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  opcode; scalar_t__ wr_id; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ ib_poll_cq (struct ib_cq*,int,struct ib_wc*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_handle_qp_err (scalar_t__,int /*<<< orphan*/ ,struct srp_target_port*) ; 

__attribute__((used)) static void srp_send_completion(struct ib_cq *cq, void *target_ptr)
{
	struct srp_target_port *target = target_ptr;
	struct ib_wc wc;
	struct srp_iu *iu;

	while (ib_poll_cq(cq, 1, &wc) > 0) {
		if (likely(wc.status == IB_WC_SUCCESS)) {
			iu = (struct srp_iu *) (uintptr_t) wc.wr_id;
			list_add(&iu->list, &target->free_tx);
		} else {
			srp_handle_qp_err(wc.status, wc.opcode, target);
		}
	}
}