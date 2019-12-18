#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Data; scalar_t__ SeqNo; } ;
struct TYPE_9__ {scalar_t__ LastRecvCompleteSeqNo; int /*<<< orphan*/  ReplyAckList; int /*<<< orphan*/  RecvSegmentList; } ;
typedef  int /*<<< orphan*/  RUDP_STACK ;
typedef  TYPE_1__ RUDP_SESSION ;
typedef  TYPE_2__ RUDP_SEGMENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddInt64Distinct (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ RUDP_MAX_NUM_ACK ; 
 int /*<<< orphan*/  RUDP_MAX_SEGMENT_SIZE ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void RUDPProcessRecvPayload(RUDP_STACK *r, RUDP_SESSION *se, UINT64 seq, void *payload_data, UINT payload_size)
{
	RUDP_SEGMENT t;
	RUDP_SEGMENT *s;
	// Validate arguments
	if (r == NULL || se == NULL || seq == 0 || payload_data == NULL || payload_size == 0 || payload_size > RUDP_MAX_SEGMENT_SIZE)
	{
		return;
	}

	if (seq > (se->LastRecvCompleteSeqNo + RUDP_MAX_NUM_ACK))
	{
		// Ignore the segment which have sequence number beyond the window size, and also not to reply an ACK
		return;
	}

	if (seq <= se->LastRecvCompleteSeqNo)
	{
		// Do not receive the segment which have the sequence number that has been already received. However, reply an ACK for it
		AddInt64Distinct(se->ReplyAckList, seq);
		return;
	}

	Zero(&t, sizeof(t));
	t.SeqNo = seq;

	s = Search(se->RecvSegmentList, &t);
	if (s != NULL)
	{
		// Do not receive the segment which have the sequence number that has been already received. However, reply an ACK for it
		AddInt64Distinct(se->ReplyAckList, seq);
		return;
	}

	// Received a segment of the new sequence number
	s = ZeroMalloc(sizeof(RUDP_SEGMENT));
	s->SeqNo = seq;
	Copy(s->Data, payload_data, payload_size);
	s->Size = payload_size;
	Insert(se->RecvSegmentList, s);

	// Reply an ACK
	AddInt64Distinct(se->ReplyAckList, seq);

	// Create a socket for session if it have not been created yet
	//RUDPInitSock(r, se);
}