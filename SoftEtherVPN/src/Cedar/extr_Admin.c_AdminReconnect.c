#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_17__ {int /*<<< orphan*/  ref; } ;
struct TYPE_16__ {int IsVpnServer; TYPE_2__* Sock; TYPE_3__* Param; int /*<<< orphan*/  VpnServerHashedPassword; int /*<<< orphan*/  VpnServerClientName; int /*<<< orphan*/  VpnServerHubName; int /*<<< orphan*/  VpnServerClientOption; } ;
struct TYPE_15__ {TYPE_1__* Connection; TYPE_5__* Cedar; } ;
struct TYPE_14__ {int /*<<< orphan*/  ref; } ;
struct TYPE_13__ {TYPE_2__* FirstSock; } ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ SESSION ;
typedef  TYPE_4__ RPC ;
typedef  TYPE_5__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 TYPE_3__* AdminConnectMain (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  HashAdminPassword (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ReleaseCedar (TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 

UINT AdminReconnect(RPC *rpc)
{
	SESSION *s;
	SOCK *sock;
	CEDAR *cedar;
	UINT err;
	bool empty_password = false;
	// Validate arguments
	if (rpc == NULL || rpc->IsVpnServer == false)
	{
		return ERR_INTERNAL_ERROR;
	}

	s = (SESSION *)rpc->Param;
	cedar = s->Cedar;
	AddRef(cedar->ref);

	sock = rpc->Sock;
	Disconnect(sock);
	ReleaseSock(sock);
	ReleaseSession(s);
	rpc->Param = NULL;

	rpc->Sock = NULL;

	s = AdminConnectMain(cedar, &rpc->VpnServerClientOption,
		rpc->VpnServerHubName,
		rpc->VpnServerHashedPassword,
		&err,
		rpc->VpnServerClientName, NULL, &empty_password);

	ReleaseCedar(cedar);

	if (s == NULL)
	{
		return err;
	}

	if (empty_password)
	{
		HashAdminPassword(rpc->VpnServerHashedPassword, "");
	}

	rpc->Param = s;
	rpc->Sock = s->Connection->FirstSock;
	AddRef(rpc->Sock->ref);

	return ERR_NO_ERROR;
}