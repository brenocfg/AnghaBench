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
struct TYPE_4__ {int /*<<< orphan*/  ServerCert; void* CheckServerCert; int /*<<< orphan*/  Policy; void* ClientAuth; void* ClientOption; void* Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_CREATE_LINK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientAuth (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcClientOption (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcCreateLink(RPC_CREATE_LINK *t, PACK *p)
{
	BUF *b;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_CREATE_LINK));
	PackGetStr(p, "HubName_Ex", t->HubName, sizeof(t->HubName));
	t->Online = PackGetBool(p, "Online");
	t->ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
	InRpcClientOption(t->ClientOption, p);
	t->ClientAuth  = ZeroMalloc(sizeof(CLIENT_AUTH));
	InRpcClientAuth(t->ClientAuth, p);
	InRpcPolicy(&t->Policy, p);

	t->CheckServerCert = PackGetBool(p, "CheckServerCert");
	b = PackGetBuf(p, "ServerCert");
	if (b != NULL)
	{
		t->ServerCert = BufToX(b, false);
		FreeBuf(b);
	}
}