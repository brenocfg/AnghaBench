#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_9__ {int ServerAdmin; int /*<<< orphan*/ * Server; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_1__ RPC_SESSION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ADMIN ;

/* Variables and functions */
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcSessionStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  InRpcSessionStatus (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcSessionStatus (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ StGetSessionStatus (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

PACK *SiCalledGetSessionStatus(SERVER *s, PACK *p)
{
	RPC_SESSION_STATUS t;
	ADMIN a;
	PACK *ret;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NULL;
	}

	Zero(&t, sizeof(t));
	InRpcSessionStatus(&t, p);

	Zero(&a, sizeof(a));
	a.Server = s;
	a.ServerAdmin = true;

	if (StGetSessionStatus(&a, &t) != ERR_NO_ERROR)
	{
		FreeRpcSessionStatus(&t);
		return NULL;
	}

	ret = NewPack();

	OutRpcSessionStatus(ret, &t);

	FreeRpcSessionStatus(&t);

	return ret;
}