#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  keygen ;
typedef  int /*<<< orphan*/  key ;
typedef  int UINT64 ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_16__ {int* Key_Recv; int YourTick; int LatestRecvMyTick; int LatestRecvMyTick2; int CurrentRtt; int Magic_Disconnect; int LastRecvTick; scalar_t__ Status; } ;
struct TYPE_15__ {scalar_t__ Protocol; int Now; int ServerMode; int /*<<< orphan*/  SvcNameHash; } ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_2__ RUDP_SESSION ;
typedef  int /*<<< orphan*/  CRYPT ;

/* Variables and functions */
 scalar_t__ Cmp (int*,int*,int) ; 
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Encrypt (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  FreeCrypt (int /*<<< orphan*/ *) ; 
 void* MAX (int,int) ; 
 int /*<<< orphan*/ * NewCrypt (int*,int) ; 
 int READ_UINT (int*) ; 
 int READ_UINT64 (int*) ; 
 int /*<<< orphan*/  RUDPDisconnectSession (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RUDPInitSock (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  RUDPProcessAck (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RUDPProcessAck2 (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RUDPProcessRecvPayload (TYPE_1__*,TYPE_2__*,int,int*,int) ; 
 int RUDP_MAX_NUM_ACK ; 
 int RUDP_MAX_SEGMENT_SIZE ; 
 scalar_t__ RUDP_PROTOCOL_DNS ; 
 scalar_t__ RUDP_PROTOCOL_ICMP ; 
 scalar_t__ RUDP_SESSION_STATUS_CONNECT_SENT ; 
 scalar_t__ RUDP_SESSION_STATUS_ESTABLISHED ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int*,int*,int) ; 
 int /*<<< orphan*/  XorData (int*,int*,int /*<<< orphan*/ ,int) ; 

bool RUDPProcessRecvPacket(RUDP_STACK *r, RUDP_SESSION *se, void *recv_data, UINT recv_size)
{
	UCHAR sign[SHA1_SIZE];
	UCHAR sign2[SHA1_SIZE];
	UCHAR *p;
	UCHAR *iv;
	UINT size;
	UCHAR keygen[SHA1_SIZE * 2];
	UCHAR key[SHA1_SIZE];
	CRYPT *c;
	UCHAR padlen;
	UINT num_ack;
	UINT i;
	UINT64 seq_no;
	UCHAR *payload;
	UINT payload_size;
	UINT64 max_ack;
	UINT64 my_tick, your_tick;
	// Validate arguments
	if (r == NULL || se == NULL || recv_data == NULL || recv_size == 0)
	{
		return false;
	}

	p = (UCHAR *)recv_data;
	size = recv_size;
	if (size < SHA1_SIZE)
	{
		return false;
	}

	// Validate the signature
	Copy(sign, p, SHA1_SIZE);
	Copy(p, se->Key_Recv, SHA1_SIZE);
	Sha1(sign2, p, recv_size);
	Copy(p, sign, SHA1_SIZE);

	if (r->Protocol == RUDP_PROTOCOL_DNS || r->Protocol == RUDP_PROTOCOL_ICMP)
	{
		XorData(sign2, sign2, r->SvcNameHash, SHA1_SIZE);
	}

	if (Cmp(sign, sign2, SHA1_SIZE) != 0)
	{
		//WHERE;
		return false;
	}
	p += SHA1_SIZE;
	size -= SHA1_SIZE;

	// IV
	if (size < SHA1_SIZE)
	{
		return false;
	}
	iv = p;
	p += SHA1_SIZE;
	size -= SHA1_SIZE;

	// Decrypt
	if (size < 1)
	{
		return false;
	}
	Copy(keygen + 0, iv, SHA1_SIZE);
	Copy(keygen + SHA1_SIZE, se->Key_Recv, SHA1_SIZE);
	Sha1(key, keygen, sizeof(keygen));

	c = NewCrypt(key, sizeof(key));
	Encrypt(c, p, p, size);
	FreeCrypt(c);

	// padlen
	padlen = p[size - 1];
	if (padlen == 0)
	{
		return false;
	}
	if (size < padlen)
	{
		return false;
	}
	size -= padlen;

	// MyTick
	if (size < sizeof(UINT64))
	{
		return false;
	}
	my_tick = READ_UINT64(p);
	p += sizeof(UINT64);
	size -= sizeof(UINT64);

	// YourTick
	if (size < sizeof(UINT64))
	{
		return false;
	}
	your_tick = READ_UINT64(p);
	p += sizeof(UINT64);
	size -= sizeof(UINT64);

	if (your_tick > r->Now)
	{
		return false;
	}

	// MAX_ACK
	if (size < sizeof(UINT64))
	{
		return false;
	}
	max_ack = READ_UINT64(p);
	p += sizeof(UINT64);
	size -= sizeof(UINT64);

	// num_ack
	if (size < sizeof(UINT))
	{
		return false;
	}

	num_ack = READ_UINT(p);
	if (num_ack > RUDP_MAX_NUM_ACK)
	{
		return false;
	}
	p += sizeof(UINT);
	size -= sizeof(UINT);

	// ACKs
	if (size < (sizeof(UINT64) * num_ack + sizeof(UINT64)))
	{
		return false;
	}

	if (max_ack >= 1)
	{
		RUDPProcessAck2(r, se, max_ack);
	}

	for (i = 0;i < num_ack;i++)
	{
		UINT64 seq = READ_UINT64(p);

		RUDPProcessAck(r, se, seq);

		p += sizeof(UINT64);
		size -= sizeof(UINT64);
	}

	// Processing of the Tick (Calculation of RTT)
	if (my_tick >= 2)
	{
		my_tick--;
	}
	se->YourTick = MAX(se->YourTick, my_tick);

	se->LatestRecvMyTick = MAX(se->LatestRecvMyTick, your_tick);

	if (se->LatestRecvMyTick2 != se->LatestRecvMyTick)
	{
		se->LatestRecvMyTick2 = se->LatestRecvMyTick;
		se->CurrentRtt = (UINT)(r->Now - se->LatestRecvMyTick);

#ifdef	RUDP_DETAIL_LOG
		Debug("CurrentRTT = %u\n", se->CurrentRtt);
#endif	// RUDP_DETAIL_LOG
	}

	// SEQ NO
	seq_no = READ_UINT64(p);
	p += sizeof(UINT64);
	size -= sizeof(UINT64);

	if (seq_no == 0)
	{
		// Sequence number of 0 is a invalid packet
		return true;
	}

	if (seq_no == se->Magic_Disconnect)
	{
		// Disconnected from opponent
		RUDPDisconnectSession(r, se, true);
		return true;
	}

	// Update the last reception date and time
	se->LastRecvTick = r->Now;

	payload = p;
	payload_size = size;

#ifdef	RUDP_DETAIL_LOG
	Debug("RUDP %X Segment Recv: %I64u (num_ack=%u, size=%u)\n", se, seq_no, num_ack, size);
#endif	// RUDP_DETAIL_LOG

	if (payload_size >= 1 && payload_size <= RUDP_MAX_SEGMENT_SIZE)
	{
		// Received one or more bytes of data

#ifdef	RUDP_DETAIL_LOG
		Debug("Recv Size: %X %I64u %u %u\n", se, seq_no, payload_size, recv_size);
#endif	// RUDP_DETAIL_LOG

		RUDPProcessRecvPayload(r, se, seq_no, payload, payload_size);
	}

	if (r->ServerMode == false)
	{
		if (se->Status == RUDP_SESSION_STATUS_CONNECT_SENT)
		{
			// Shift to the established state if the connection is not yet in established state
			se->Status = RUDP_SESSION_STATUS_ESTABLISHED;

			RUDPInitSock(r, se);
		}
	}

	return true;
}