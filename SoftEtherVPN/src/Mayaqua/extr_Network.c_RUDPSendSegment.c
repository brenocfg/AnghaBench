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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {scalar_t__ SeqNo; int /*<<< orphan*/  Size; int /*<<< orphan*/  Data; } ;
struct TYPE_6__ {int /*<<< orphan*/  SendSegmentList; int /*<<< orphan*/  NextSendSeqNo; } ;
typedef  int /*<<< orphan*/  RUDP_STACK ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  TYPE_2__ RUDP_SEGMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  RUDP_MAX_SEGMENT_SIZE ; 
 TYPE_2__* ZeroMalloc (int) ; 

void RUDPSendSegment(RUDP_STACK *r, RUDP_SESSION *se, void *data, UINT size)
{
	RUDP_SEGMENT *s;
	// Validate arguments
	if (r == NULL || se == NULL || (size != 0 && data == NULL) || (size > RUDP_MAX_SEGMENT_SIZE))
	{
		return;
	}

	s = ZeroMalloc(sizeof(RUDP_SEGMENT));

	Copy(s->Data, data, size);
	s->Size = size;

	s->SeqNo = se->NextSendSeqNo++;

	Insert(se->SendSegmentList, s);
}