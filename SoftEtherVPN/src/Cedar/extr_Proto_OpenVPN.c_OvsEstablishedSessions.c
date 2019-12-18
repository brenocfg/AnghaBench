#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * SessionList; } ;
struct TYPE_4__ {scalar_t__ Established; } ;
typedef  TYPE_1__ OPENVPN_SESSION ;
typedef  TYPE_2__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

UINT OvsEstablishedSessions(void *param)
{
	LIST *sessions;
	UINT i;
	UINT established_sessions = 0;

	if (param == NULL)
	{
		return 0;
	}

	sessions = ((OPENVPN_SERVER *)param)->SessionList;

	for (i = 0;i < LIST_NUM(sessions);i++)
	{
		OPENVPN_SESSION *se = LIST_DATA(sessions, i);

		if (se->Established)
		{
			++established_sessions;
		}
	}

	return established_sessions;
}