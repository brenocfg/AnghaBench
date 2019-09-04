#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {TYPE_2__* Server; } ;
struct TYPE_12__ {int Online; int /*<<< orphan*/  lock; int /*<<< orphan*/  NumFailed; int /*<<< orphan*/  NumTry; int /*<<< orphan*/  NumConnected; int /*<<< orphan*/  FirstConnectedTime; int /*<<< orphan*/  StartedTime; int /*<<< orphan*/  CurrentConnectedTime; int /*<<< orphan*/  LastError; TYPE_1__* Sock; } ;
struct TYPE_11__ {int Online; int /*<<< orphan*/  NumFailed; int /*<<< orphan*/  NumTry; int /*<<< orphan*/  NumConnected; int /*<<< orphan*/  FirstConnectedTime; int /*<<< orphan*/  StartedTime; int /*<<< orphan*/  CurrentConnectedTime; int /*<<< orphan*/  LastError; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; } ;
struct TYPE_10__ {scalar_t__ ServerType; TYPE_4__* FarmController; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_9__ {int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_FARM_CONNECTION_STATUS ;
typedef  TYPE_4__ FARM_CONTROLLER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_5__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOT_FARM_MEMBER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StGetFarmConnectionStatus(ADMIN *a, RPC_FARM_CONNECTION_STATUS *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	FARM_CONTROLLER *fc;

	if (s->ServerType != SERVER_TYPE_FARM_MEMBER)
	{
		return ERR_NOT_FARM_MEMBER;
	}

	Zero(t, sizeof(RPC_FARM_CONNECTION_STATUS));

	fc = s->FarmController;

	Lock(fc->lock);
	{
		if (fc->Sock != NULL)
		{
			t->Ip = IPToUINT(&fc->Sock->RemoteIP);
			t->Port = fc->Sock->RemotePort;
		}

		t->Online = fc->Online;
		t->LastError = ERR_NO_ERROR;

		if (t->Online == false)
		{
			t->LastError = fc->LastError;
		}
		else
		{
			t->CurrentConnectedTime = fc->CurrentConnectedTime;
		}

		t->StartedTime = fc->StartedTime;
		t->FirstConnectedTime = fc->FirstConnectedTime;

		t->NumConnected = fc->NumConnected;
		t->NumTry = fc->NumTry;
		t->NumFailed = fc->NumFailed;
	}
	Unlock(fc->lock);

	return ERR_NO_ERROR;
}