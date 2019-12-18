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
struct TYPE_3__ {void* neighbor_discovery_context; int /*<<< orphan*/  neighbor_discovery; } ;
typedef  TYPE_1__ ccv_nnc_stream_context_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_neighbor_discovery_f ;

/* Variables and functions */

void ccv_nnc_stream_context_set_neighbor_discovery(ccv_nnc_stream_context_t* const stream_context, ccv_nnc_stream_context_neighbor_discovery_f discovery, void* const context)
{
	stream_context->neighbor_discovery = discovery;
	stream_context->neighbor_discovery_context = context;
}