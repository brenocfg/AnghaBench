#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ SeqNo; } ;
struct TYPE_8__ {int /*<<< orphan*/ * SendSegmentList; } ;
typedef  int /*<<< orphan*/  RUDP_STACK ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  TYPE_2__ RUDP_SEGMENT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void RUDPProcessAck2(RUDP_STACK *r, RUDP_SESSION *se, UINT64 max_seq)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (r == NULL || se == NULL || max_seq == 0)
	{
		return;
	}

	o = NULL;

	for (i = 0;i < LIST_NUM(se->SendSegmentList);i++)
	{
		RUDP_SEGMENT *s = LIST_DATA(se->SendSegmentList, i);

		if (s->SeqNo <= max_seq)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, s);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			RUDP_SEGMENT *s = LIST_DATA(o, i);

			Delete(se->SendSegmentList, s);

			Free(s);
		}

		ReleaseList(o);
	}
}