#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  notify; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ ccv_nnc_stream_scheduler_t ;
struct TYPE_6__ {TYPE_1__* scheduler; } ;
typedef  TYPE_2__ ccv_nnc_stream_context_t ;

/* Variables and functions */
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ccv_nnc_stream_scheduler_t* ccv_nnc_stream_context_get_scheduler(ccv_nnc_stream_context_t* const stream_context)
{
	ccv_nnc_stream_scheduler_t* scheduler = stream_context->scheduler;
	if (!scheduler)
	{
		stream_context->scheduler = scheduler = (ccv_nnc_stream_scheduler_t*)cccalloc(1, sizeof(ccv_nnc_stream_scheduler_t));
		pthread_mutex_init(&scheduler->mutex, 0);
		pthread_cond_init(&scheduler->notify, 0);
		pthread_cond_init(&scheduler->wait, 0);
	}
	return scheduler;
}