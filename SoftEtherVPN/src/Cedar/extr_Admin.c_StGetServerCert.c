#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ServerK; int /*<<< orphan*/  ServerX; } ;
struct TYPE_10__ {int /*<<< orphan*/  Key; int /*<<< orphan*/  Cert; } ;
struct TYPE_9__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_KEY_PAIR ;
typedef  TYPE_3__ CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CloneK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcKeyPair (TYPE_2__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StGetServerCert(ADMIN *a, RPC_KEY_PAIR *t)
{
	bool admin;
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	bool is_vgs_cert = false;

	admin = a->ServerAdmin;

	FreeRpcKeyPair(t);
	Zero(t, sizeof(RPC_KEY_PAIR));

	Lock(c->lock);
	{

		t->Cert = CloneX(c->ServerX);
		if (admin && is_vgs_cert == false)
		{
			t->Key = CloneK(c->ServerK);
		}
	}
	Unlock(c->lock);

	return ERR_NO_ERROR;
}