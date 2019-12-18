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
struct TYPE_2__ {scalar_t__ count; } ;
struct raw3270_request {scalar_t__ size; scalar_t__ buffer; TYPE_1__ ccw; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 

int
raw3270_request_add_data(struct raw3270_request *rq, void *data, size_t size)
{
	if (size + rq->ccw.count > rq->size)
		return -E2BIG;
	memcpy(rq->buffer + rq->ccw.count, data, size);
	rq->ccw.count += size;
	return 0;
}