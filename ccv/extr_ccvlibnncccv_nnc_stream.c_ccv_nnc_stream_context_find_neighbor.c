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
struct TYPE_5__ {int /*<<< orphan*/  neighbor_discovery_context; TYPE_1__* (* neighbor_discovery ) (int const,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ccv_nnc_stream_context_t ;

/* Variables and functions */
 TYPE_1__* stub1 (int const,int /*<<< orphan*/ ) ; 

ccv_nnc_stream_context_t* ccv_nnc_stream_context_find_neighbor(ccv_nnc_stream_context_t* const stream_context, const int device_id)
{
	if (stream_context->neighbor_discovery)
		return stream_context->neighbor_discovery(device_id, stream_context->neighbor_discovery_context);
	return 0;
}