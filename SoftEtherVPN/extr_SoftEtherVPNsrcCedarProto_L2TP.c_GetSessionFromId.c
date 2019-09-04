#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ SessionId2; } ;
struct TYPE_6__ {int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SESSION ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

L2TP_SESSION *GetSessionFromId(L2TP_TUNNEL *t, UINT session_id)
{
	UINT i;
	// Validate arguments
	if (t == NULL || session_id == 0)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(t->SessionList);i++)
	{
		L2TP_SESSION *s = LIST_DATA(t->SessionList, i);

		if (s->SessionId2 == session_id)
		{
			return s;
		}
	}

	return NULL;
}