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
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_rpc_endpoint* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_rpc_endpoint* msm_rpcrouter_create_local_endpoint (int /*<<< orphan*/ ) ; 

struct msm_rpc_endpoint *msm_rpc_open(void)
{
	struct msm_rpc_endpoint *ept;

	ept = msm_rpcrouter_create_local_endpoint(MKDEV(0, 0));
	if (ept == NULL)
		return ERR_PTR(-ENOMEM);

	return ept;
}