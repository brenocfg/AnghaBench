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
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_6__ {int /*<<< orphan*/  SeqNo; } ;
struct TYPE_5__ {int /*<<< orphan*/  SendSegmentList; } ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  TYPE_2__ RUDP_SEGMENT ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

UINT64 RUDPGetCurrentSendingMaxSeqNo(RUDP_SESSION *se)
{
	RUDP_SEGMENT *s;
	// Validate arguments
	if (se == NULL)
	{
		return 0;
	}

	if (LIST_NUM(se->SendSegmentList) == 0)
	{
		return 0;
	}

	s = LIST_DATA(se->SendSegmentList, (LIST_NUM(se->SendSegmentList) - 1));

	return s->SeqNo;
}