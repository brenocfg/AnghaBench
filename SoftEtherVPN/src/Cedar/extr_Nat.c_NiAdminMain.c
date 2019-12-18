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
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  RPC ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  NAT ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HttpServerSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  NiRpcServer ; 
 int /*<<< orphan*/  RpcFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcServer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StartRpcServer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void NiAdminMain(NAT *n, SOCK *s)
{
	RPC *r;
	PACK *p;
	// Validate arguments
	if (n == NULL || s == NULL)
	{
		return;
	}

	p = NewPack();
	HttpServerSend(s, p);
	FreePack(p);

	r = StartRpcServer(s, NiRpcServer, n);

	RpcServer(r);

	RpcFree(r);
}