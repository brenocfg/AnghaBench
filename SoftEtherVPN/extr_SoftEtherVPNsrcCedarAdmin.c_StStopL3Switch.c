#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {TYPE_1__* Server; } ;
struct TYPE_14__ {int /*<<< orphan*/  Name; } ;
struct TYPE_13__ {int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_L3SW ;
typedef  TYPE_3__ L3SW ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_LAYER3_SW_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* L3GetSw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3SwStop (TYPE_3__*) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseL3Sw (TYPE_3__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 

UINT StStopL3Switch(ADMIN *a, RPC_L3SW *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	L3SW *sw;

	if (IsEmptyStr(t->Name))
	{
		return ERR_INVALID_PARAMETER;
	}

	NO_SUPPORT_FOR_BRIDGE;

	SERVER_ADMIN_ONLY;

	sw = L3GetSw(c, t->Name);

	if (sw == NULL)
	{
		ret = ERR_LAYER3_SW_NOT_FOUND;
	}
	else
	{
		L3SwStop(sw);
		ALog(a, NULL, "LA_STOP_L3_SW", sw->Name);
		ReleaseL3Sw(sw);

		IncrementServerConfigRevision(s);
	}

	return ret;
}