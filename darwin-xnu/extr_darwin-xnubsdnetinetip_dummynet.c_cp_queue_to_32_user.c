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
struct dn_flow_queue_32 {int /*<<< orphan*/  F; int /*<<< orphan*/  S; int /*<<< orphan*/  sched_time; int /*<<< orphan*/  heap_pos; int /*<<< orphan*/  q_time; int /*<<< orphan*/  random; int /*<<< orphan*/  count; int /*<<< orphan*/  avg; int /*<<< orphan*/  hash_slot; int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  numbytes; int /*<<< orphan*/  len_bytes; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct dn_flow_queue {int /*<<< orphan*/  F; int /*<<< orphan*/  S; int /*<<< orphan*/  sched_time; int /*<<< orphan*/  heap_pos; int /*<<< orphan*/  q_time; int /*<<< orphan*/  random; int /*<<< orphan*/  count; int /*<<< orphan*/  avg; int /*<<< orphan*/  hash_slot; int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  numbytes; int /*<<< orphan*/  len_bytes; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */

__attribute__((used)) static
void cp_queue_to_32_user( struct dn_flow_queue *q, struct dn_flow_queue_32 *qp)
{
	qp->id = q->id;
	qp->len = q->len;
	qp->len_bytes = q->len_bytes;
	qp->numbytes = q->numbytes;
	qp->tot_pkts = q->tot_pkts;
	qp->tot_bytes = q->tot_bytes;
	qp->drops = q->drops;
	qp->hash_slot = q->hash_slot;
	qp->avg = q->avg;
	qp->count = q->count;
	qp->random = q->random;
	qp->q_time = q->q_time;
	qp->heap_pos = q->heap_pos;
	qp->sched_time = q->sched_time;
	qp->S = q->S;
	qp->F = q->F;
}