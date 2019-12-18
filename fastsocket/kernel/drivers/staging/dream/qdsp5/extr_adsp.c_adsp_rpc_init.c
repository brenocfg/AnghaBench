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
struct msm_adsp_module {scalar_t__ rpc_client; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MSM_RPC_UNINTERRUPTIBLE ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_ATOM_PROG ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_ATOM_VERS ; 
 scalar_t__ msm_rpc_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int adsp_rpc_init(struct msm_adsp_module *adsp_module)
{
	/* remove the original connect once compatible support is complete */
	adsp_module->rpc_client = msm_rpc_connect(
			RPC_ADSP_RTOS_ATOM_PROG,
			RPC_ADSP_RTOS_ATOM_VERS,
			MSM_RPC_UNINTERRUPTIBLE);

	if (IS_ERR(adsp_module->rpc_client)) {
		int rc = PTR_ERR(adsp_module->rpc_client);
		adsp_module->rpc_client = 0;
		pr_err("adsp: could not open rpc client: %d\n", rc);
		return rc;
	}

	return 0;
}