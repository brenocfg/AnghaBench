#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int IsV3; TYPE_1__* Tunnel; int /*<<< orphan*/  IsCiscoV3; scalar_t__ SessionId2; scalar_t__ SessionId1; } ;
struct TYPE_7__ {int IsV3; int /*<<< orphan*/  IsCiscoV3; int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SESSION ;
typedef  int /*<<< orphan*/  L2TP_SERVER ;

/* Variables and functions */
 scalar_t__ GenerateNewSessionIdEx (TYPE_1__*,int) ; 
 scalar_t__ GenerateNewSessionIdForL2TPv3 (int /*<<< orphan*/ *) ; 
 scalar_t__ L2TP_QUOTA_MAX_NUM_SESSIONS_PER_TUNNEL ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

L2TP_SESSION *NewL2TPSession(L2TP_SERVER *l2tp, L2TP_TUNNEL *t, UINT session_id_by_client)
{
	L2TP_SESSION *s;
	UINT session_id_by_server;
	// Validate arguments
	if (l2tp == NULL || t == NULL || session_id_by_client == 0)
	{
		return NULL;
	}

	if (LIST_NUM(t->SessionList) >= L2TP_QUOTA_MAX_NUM_SESSIONS_PER_TUNNEL)
	{
		return NULL;
	}

	if (t->IsV3 == false)
	{
		session_id_by_server = GenerateNewSessionIdEx(t, t->IsV3);
	}
	else
	{
		session_id_by_server = GenerateNewSessionIdForL2TPv3(l2tp);
	}
	if (session_id_by_server == 0)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(L2TP_SESSION));

	s->SessionId1 = session_id_by_client;
	s->SessionId2 = session_id_by_server;

	s->IsV3 = t->IsV3;
	s->IsCiscoV3 = t->IsCiscoV3;

	s->Tunnel = t;

	return s;
}