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
struct request {struct request* completion_data; struct dm_rq_target_io* end_io_data; } ;
struct dm_rq_target_io {int error; struct request* orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_complete_request (struct request*) ; 

__attribute__((used)) static void dm_complete_request(struct request *clone, int error)
{
	struct dm_rq_target_io *tio = clone->end_io_data;
	struct request *rq = tio->orig;

	tio->error = error;
	rq->completion_data = clone;
	blk_complete_request(rq);
}