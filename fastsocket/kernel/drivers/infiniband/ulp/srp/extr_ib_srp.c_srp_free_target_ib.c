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
struct srp_target_port {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  srp_host; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * recv_cq; int /*<<< orphan*/ * send_cq; int /*<<< orphan*/ * qp; } ;

/* Variables and functions */
 int SRP_RQ_SIZE ; 
 int SRP_SQ_SIZE ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_free_iu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_free_target_ib(struct srp_target_port *target)
{
	int i;

	ib_destroy_qp(target->qp);
	ib_destroy_cq(target->send_cq);
	ib_destroy_cq(target->recv_cq);

	target->qp = NULL;
	target->send_cq = target->recv_cq = NULL;

	for (i = 0; i < SRP_RQ_SIZE; ++i)
		srp_free_iu(target->srp_host, target->rx_ring[i]);
	for (i = 0; i < SRP_SQ_SIZE; ++i)
		srp_free_iu(target->srp_host, target->tx_ring[i]);
}