#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_nnc_stream_signal_t ;

/* Variables and functions */
 scalar_t__ CCV_STREAM_CONTEXT_GPU ; 
 scalar_t__ CCV_STREAM_GET_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccfree (TYPE_1__* const) ; 
 int /*<<< orphan*/  ccv_nnc_deinit_stream_signal (TYPE_1__* const) ; 

void ccv_nnc_stream_signal_free(ccv_nnc_stream_signal_t* const signal)
{
#ifdef HAVE_CUDA
	if (CCV_STREAM_GET_CONTEXT(signal->type) == CCV_STREAM_CONTEXT_GPU)
		ccv_nnc_deinit_stream_signal(signal);
#endif
	ccfree(signal);
}