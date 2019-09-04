#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {TYPE_1__* Server; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  String; } ;
struct TYPE_10__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_STR ;
typedef  TYPE_3__ CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SetCedarCipherList (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrUpper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT StSetServerCipher(ADMIN *a, RPC_STR *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;

	if (IsEmptyStr(t->String))
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;

	StrUpper(t->String);

	ALog(a, NULL, "LA_SET_SERVER_CIPHER", t->String);

	Lock(c->lock);
	{
		SetCedarCipherList(c, t->String);
	}
	Unlock(c->lock);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}