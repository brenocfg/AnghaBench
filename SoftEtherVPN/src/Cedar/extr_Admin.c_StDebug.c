#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t2 ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {TYPE_1__* Server; } ;
struct TYPE_12__ {int /*<<< orphan*/  StrValue; int /*<<< orphan*/  IntValue; } ;
struct TYPE_11__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_TEST ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 scalar_t__ SiDebug (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StDebug(ADMIN *a, RPC_TEST *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	RPC_TEST t2;

	SERVER_ADMIN_ONLY;

	Zero(&t2, sizeof(t2));

	ret = SiDebug(s, &t2, t->IntValue, t->StrValue);

	if (ret == ERR_NO_ERROR)
	{
		Copy(t, &t2, sizeof(RPC_TEST));
	}
	else
	{
		Zero(t, sizeof(RPC_TEST));
	}

	return ret;
}