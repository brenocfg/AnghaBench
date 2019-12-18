#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */

__attribute__((used)) static ccv_nnc_stream_context_t* _neighbor_discovery(const int device_id, void* const contexts)
{
	ccv_nnc_stream_context_t** stream_contexts = (ccv_nnc_stream_context_t**)contexts;
	return stream_contexts[device_id];
}