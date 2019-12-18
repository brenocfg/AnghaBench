#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_stream_task_t ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_nnc_stream_context_t ;

/* Variables and functions */
 scalar_t__ CCV_STREAM_CONTEXT_GPU ; 
 scalar_t__ CCV_STREAM_GET_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_stream_compat_task_synchronize (int /*<<< orphan*/ * const,TYPE_1__* const) ; 

void ccv_nnc_stream_task_synchronize(ccv_nnc_stream_task_t* const self, ccv_nnc_stream_context_t* const stream)
{
	if (!stream)
		return;
#ifdef HAVE_CUDA
	if (CCV_STREAM_GET_CONTEXT(stream->type) == CCV_STREAM_CONTEXT_GPU)
		ccv_nnc_stream_compat_task_synchronize(self, stream);
#endif
}