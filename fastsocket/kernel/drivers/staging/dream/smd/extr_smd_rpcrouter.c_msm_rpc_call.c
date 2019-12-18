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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_rpc_endpoint {int dummy; } ;

/* Variables and functions */
 int msm_rpc_call_reply (struct msm_rpc_endpoint*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

int msm_rpc_call(struct msm_rpc_endpoint *ept, uint32_t proc,
		 void *_request, int request_size,
		 long timeout)
{
	return msm_rpc_call_reply(ept, proc,
				  _request, request_size,
				  NULL, 0, timeout);
}