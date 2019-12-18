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
struct request {int dummy; } ;
struct deadline_data {int /*<<< orphan*/  last_sector; int /*<<< orphan*/ ** next_rq; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/ * deadline_latter_request (struct request*) ; 
 int /*<<< orphan*/  deadline_move_to_dispatch (struct deadline_data*,struct request*) ; 
 int rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_end_sector (struct request*) ; 

__attribute__((used)) static void
deadline_move_request(struct deadline_data *dd, struct request *rq)
{
	const int data_dir = rq_data_dir(rq);

	dd->next_rq[READ] = NULL;
	dd->next_rq[WRITE] = NULL;
	dd->next_rq[data_dir] = deadline_latter_request(rq);

	dd->last_sector = rq_end_sector(rq);

	/*
	 * take it off the sort and fifo list, move
	 * to dispatch queue
	 */
	deadline_move_to_dispatch(dd, rq);
}