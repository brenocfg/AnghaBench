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
struct TYPE_12__ {TYPE_1__* Server; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  CipherList; } ;
struct TYPE_10__ {int /*<<< orphan*/  String; } ;
struct TYPE_9__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_STR ;
typedef  TYPE_3__ CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcStr (TYPE_2__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StGetServerCipher(ADMIN *a, RPC_STR *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;

	FreeRpcStr(t);
	Zero(t, sizeof(RPC_STR));

	Lock(c->lock);
	{
		t->String = CopyStr(c->CipherList);
	}
	Unlock(c->lock);

	return ERR_NO_ERROR;
}