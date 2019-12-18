#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Rpc; } ;
typedef  int /*<<< orphan*/  RPC_CLIENT_CONNECT ;
typedef  TYPE_1__ REMOTE_CLIENT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  CcSetServiceToForegroundProcess (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcClientConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RpcCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcGetError (int /*<<< orphan*/ *) ; 
 int RpcIsOk (int /*<<< orphan*/ *) ; 

UINT CcConnect(REMOTE_CLIENT *r, RPC_CLIENT_CONNECT *connect)
{
	PACK *ret, *p;
	UINT err = 0;
	// Validate arguments
	if (r == NULL || connect == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	CcSetServiceToForegroundProcess(r);

	p = NewPack();
	OutRpcClientConnect(p, connect);

	ret = RpcCall(r->Rpc, "Connect", p);

	if (RpcIsOk(ret) == false)
	{
		err = RpcGetError(ret);
	}

	FreePack(ret);

	return err;
}