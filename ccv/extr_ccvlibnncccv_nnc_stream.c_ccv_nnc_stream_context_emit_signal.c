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
struct TYPE_3__ {int /*<<< orphan*/ * emit_context; } ;
typedef  TYPE_1__ ccv_nnc_stream_signal_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */

void ccv_nnc_stream_context_emit_signal(ccv_nnc_stream_context_t* const stream, ccv_nnc_stream_signal_t* const signal)
{
	signal->emit_context = stream;
#ifdef HAVE_CUDA
	if (CCV_STREAM_GET_CONTEXT(signal->type) == CCV_STREAM_CONTEXT_GPU)
		ccv_nnc_stream_compat_emit_signal(stream, signal);
#endif
}