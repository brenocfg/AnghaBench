#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  signal_container; } ;
struct TYPE_4__ {scalar_t__ workspace; scalar_t__ workspace_size; TYPE_1__ super; } ;
typedef  TYPE_2__ ccv_nnc_stream_cpu_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */
 scalar_t__ CCV_STREAM_CONTEXT_GPU ; 
 scalar_t__ CCV_STREAM_GET_CONTEXT (int const) ; 
 scalar_t__ cccalloc (int,int) ; 
 int /*<<< orphan*/ * ccv_nnc_init_stream_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_container ; 

ccv_nnc_stream_context_t* ccv_nnc_stream_context_new(const int type)
{
	ccv_nnc_stream_cpu_t* const stream_cpu = (ccv_nnc_stream_cpu_t*)cccalloc(1, sizeof(ccv_nnc_stream_cpu_t));
	stream_cpu->super.type = type;
	stream_cpu->super.signal_container = kh_init(signal_container);
	stream_cpu->workspace_size = 0;
	stream_cpu->workspace = 0;
#ifdef HAVE_CUDA
	if (CCV_STREAM_GET_CONTEXT(type) == CCV_STREAM_CONTEXT_GPU)
		return ccv_nnc_init_stream_context((ccv_nnc_stream_context_t*)stream_cpu);
#endif
	return (ccv_nnc_stream_context_t*)stream_cpu;
}