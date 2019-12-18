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
struct ipzu_queue_resp {int /*<<< orphan*/  offset; int /*<<< orphan*/  toggle_state; int /*<<< orphan*/  pagesize; int /*<<< orphan*/  queue_length; int /*<<< orphan*/  act_nr_of_sg; int /*<<< orphan*/  qe_size; } ;
struct ipz_queue {int /*<<< orphan*/  offset; int /*<<< orphan*/  toggle_state; int /*<<< orphan*/  pagesize; int /*<<< orphan*/  queue_length; int /*<<< orphan*/  act_nr_of_sg; int /*<<< orphan*/  qe_size; } ;

/* Variables and functions */

__attribute__((used)) static inline void queue2resp(struct ipzu_queue_resp *resp,
			      struct ipz_queue *queue)
{
	resp->qe_size = queue->qe_size;
	resp->act_nr_of_sg = queue->act_nr_of_sg;
	resp->queue_length = queue->queue_length;
	resp->pagesize = queue->pagesize;
	resp->toggle_state = queue->toggle_state;
	resp->offset = queue->offset;
}