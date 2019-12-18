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
struct msm_rpc_endpoint {int dummy; } ;

/* Variables and functions */
 int msm_rpcrouter_destroy_local_endpoint (struct msm_rpc_endpoint*) ; 

int msm_rpc_close(struct msm_rpc_endpoint *ept)
{
	return msm_rpcrouter_destroy_local_endpoint(ept);
}