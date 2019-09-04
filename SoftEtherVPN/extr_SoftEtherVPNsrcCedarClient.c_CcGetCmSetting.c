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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Rpc; } ;
typedef  TYPE_1__ REMOTE_CLIENT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CM_SETTING ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcCmSetting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RpcCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcGetError (int /*<<< orphan*/ *) ; 
 scalar_t__ RpcIsOk (int /*<<< orphan*/ *) ; 

UINT CcGetCmSetting(REMOTE_CLIENT *r, CM_SETTING *a)
{
	PACK *ret;
	// Validate arguments
	if (r == NULL || a == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	ret = RpcCall(r->Rpc, "GetCmSetting", NULL);

	if (RpcIsOk(ret))
	{
		InRpcCmSetting(a, ret);
		FreePack(ret);
		return 0;
	}
	else
	{
		UINT err = RpcGetError(ret);
		FreePack(ret);
		return err;
	}
}