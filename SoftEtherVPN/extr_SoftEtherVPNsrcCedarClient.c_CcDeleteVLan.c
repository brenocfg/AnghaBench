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
typedef  int /*<<< orphan*/  RPC_CLIENT_CREATE_VLAN ;
typedef  TYPE_1__ REMOTE_CLIENT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcCreateVLan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RpcCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcGetError (int /*<<< orphan*/ *) ; 
 int RpcIsOk (int /*<<< orphan*/ *) ; 

UINT CcDeleteVLan(REMOTE_CLIENT *r, RPC_CLIENT_CREATE_VLAN *d)
{
	PACK *ret, *p;
	UINT err = 0;
	// Validate arguments
	if (r == NULL || d == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	p = NewPack();
	OutRpcCreateVLan(p, d);

	ret = RpcCall(r->Rpc, "DeleteVLan", p);

	if (RpcIsOk(ret) == false)
	{
		err = RpcGetError(ret);
	}

	FreePack(ret);

	return err;
}