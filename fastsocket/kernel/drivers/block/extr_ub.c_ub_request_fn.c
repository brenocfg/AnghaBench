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
struct ub_lun {int dummy; } ;
struct request_queue {struct ub_lun* queuedata; } ;
struct request {int dummy; } ;

/* Variables and functions */
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 scalar_t__ ub_request_fn_1 (struct ub_lun*,struct request*) ; 

__attribute__((used)) static void ub_request_fn(struct request_queue *q)
{
	struct ub_lun *lun = q->queuedata;
	struct request *rq;

	while ((rq = blk_peek_request(q)) != NULL) {
		if (ub_request_fn_1(lun, rq) != 0) {
			blk_stop_queue(q);
			break;
		}
	}
}