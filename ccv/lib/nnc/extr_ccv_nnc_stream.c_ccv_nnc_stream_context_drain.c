#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ workspace_size; scalar_t__ workspace; } ;
typedef  TYPE_1__ ccv_nnc_stream_cpu_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (scalar_t__) ; 
 TYPE_1__ ccv_nnc_per_thread_stream_cpu ; 
 int /*<<< orphan*/  ccv_nnc_stream_compat_drain (int /*<<< orphan*/ * const) ; 

void ccv_nnc_stream_context_drain(ccv_nnc_stream_context_t* const stream_context)
{
#ifdef HAVE_CUDA
	ccv_nnc_stream_compat_drain(stream_context);
#else
	ccv_nnc_stream_cpu_t* stream_cpu = (ccv_nnc_stream_cpu_t*)stream_context;
	if (!stream_cpu)
		stream_cpu = &ccv_nnc_per_thread_stream_cpu;
	if (stream_cpu->workspace)
	{
		ccfree(stream_cpu->workspace);
		stream_cpu->workspace = 0;
		stream_cpu->workspace_size = 0;
	}
#endif
}