#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ RPC_GET_ISSUER ;
typedef  TYPE_2__ REMOTE_CLIENT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcGetIssuer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcGetIssuer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * RpcCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcGetError (int /*<<< orphan*/ *) ; 
 scalar_t__ RpcIsOk (int /*<<< orphan*/ *) ; 

UINT CcGetIssuer(REMOTE_CLIENT *r, RPC_GET_ISSUER *a)
{
	PACK *p, *ret;
	UINT err = 0;
	// Validate arguments
	if (r == NULL || a == NULL)
	{
		return ERR_INTERNAL_ERROR;
	}

	p = NewPack();
	OutRpcGetIssuer(p, a);

	ret = RpcCall(r->Rpc, "GetIssuer", p);

	if (RpcIsOk(ret))
	{
		if (a->x != NULL)
		{
			FreeX(a->x);
			a->x = NULL;
		}
		InRpcGetIssuer(a, ret);
	}
	else
	{
		err = RpcGetError(ret);
	}

	FreePack(ret);

	return err;
}