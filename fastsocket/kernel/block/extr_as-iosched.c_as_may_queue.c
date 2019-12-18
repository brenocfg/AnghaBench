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
struct request_queue {int /*<<< orphan*/  node; TYPE_1__* elevator; } ;
struct io_context {int dummy; } ;
struct as_data {scalar_t__ antic_status; struct io_context* io_context; } ;
struct TYPE_2__ {struct as_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ ANTIC_WAIT_NEXT ; 
 scalar_t__ ANTIC_WAIT_REQ ; 
 int ELV_MQUEUE_MAY ; 
 int ELV_MQUEUE_MUST ; 
 struct io_context* as_get_io_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 

__attribute__((used)) static int as_may_queue(struct request_queue *q, int rw)
{
	int ret = ELV_MQUEUE_MAY;
	struct as_data *ad = q->elevator->elevator_data;
	struct io_context *ioc;
	if (ad->antic_status == ANTIC_WAIT_REQ ||
			ad->antic_status == ANTIC_WAIT_NEXT) {
		ioc = as_get_io_context(q->node);
		if (ad->io_context == ioc)
			ret = ELV_MQUEUE_MUST;
		put_io_context(ioc);
	}

	return ret;
}