#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  count; int /*<<< orphan*/  cda; } ;
struct raw3270_request {TYPE_1__ ccw; } ;
struct idal_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_IDA ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 

void
raw3270_request_set_idal(struct raw3270_request *rq, struct idal_buffer *ib)
{
	rq->ccw.cda = __pa(ib->data);
	rq->ccw.count = ib->size;
	rq->ccw.flags |= CCW_FLAG_IDA;
}