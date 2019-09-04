#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  SessionList; } ;
struct TYPE_5__ {scalar_t__ ServerSessionId; } ;
typedef  TYPE_1__ OPENVPN_SESSION ;
typedef  TYPE_2__ OPENVPN_SERVER ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ Rand64 () ; 

UINT64 OvsNewServerSessionId(OPENVPN_SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	while (true)
	{
		UINT64 id = Rand64();
		UINT i;
		bool exists = false;

		if (id == 0 || id == (UINT64)(0xFFFFFFFFFFFFFFFFULL))
		{
			continue;
		}

		for (i = 0;i < LIST_NUM(s->SessionList);i++)
		{
			OPENVPN_SESSION *se = LIST_DATA(s->SessionList, i);
			if (se->ServerSessionId == id)
			{
				exists = true;
			}
		}

		if (exists == false)
		{
			return id;
		}
	}
}