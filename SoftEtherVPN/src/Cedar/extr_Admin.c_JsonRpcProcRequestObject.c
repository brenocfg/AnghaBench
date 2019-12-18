#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {TYPE_1__* Server; int /*<<< orphan*/ * Rpc; } ;
struct TYPE_9__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
struct TYPE_8__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  AdminDispatch ; 
 int /*<<< orphan*/ * CallRpcDispatcher (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonRpcNewError (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonRpcNewResponse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * PackError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RpcFreeEx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * StartRpcServer (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  _E (scalar_t__) ; 

JSON_VALUE *JsonRpcProcRequestObject(ADMIN *admin, CONNECTION *c, SOCK *s, JSON_VALUE *json_req, char *method_name)
{
	PACK *pack_request;
	JSON_VALUE *ret = NULL;
	if (c == NULL || s == NULL || json_req == NULL || admin == NULL)
	{
		return NULL;
	}

	pack_request = JsonToPack(json_req);

	PackAddStr(pack_request, "function_name", method_name);

	if (pack_request != NULL)
	{
		RPC *rpc;
		PACK *pack_response;
		UINT err;

		// RPC Server
		rpc = StartRpcServer(s, AdminDispatch, admin);

		admin->Rpc = rpc;

		pack_response = CallRpcDispatcher(rpc, pack_request);

		if (pack_response == NULL)
		{
			pack_response = PackError(ERR_NOT_SUPPORTED);
		}

		RpcFreeEx(rpc, true);

		FreePack(pack_request);

		// Construct response object
		err = GetErrorFromPack(pack_response);
		if (err != 0)
		{
			// Return the error
			ret = JsonRpcNewError(err, _E(err));
		}
		else
		{
			// Return the PACK
			ret = JsonRpcNewResponse(pack_response);
		}

		SLog(admin->Server->Cedar, "LS_API_RPC_CALL",
			&s->RemoteIP, s->RemotePort, s->RemoteHostname,
			method_name, err, _E(err));

		FreePack(pack_response);
	}

	return ret;
}