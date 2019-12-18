#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  float UCHAR ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ Cmp (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (float*) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetNextIntervalForInterrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 float* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/ * NewInterruptManager () ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int /*<<< orphan*/ * NewUDP6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RecvFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,float*,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_LATER ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,float*,int) ; 
 int /*<<< orphan*/  StrLen (int /*<<< orphan*/ ) ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ UDP_FILE_QUERY_DST_PORT ; 
 int /*<<< orphan*/  UDP_FILE_QUERY_MAGIC_NUMBER ; 
 scalar_t__ UDP_FILE_QUERY_RETRY_INTERVAL ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,float*,scalar_t__) ; 

BUF *QueryFileByIPv6Udp(LIST *ip_list, UINT timeout, bool *cancel)
{
	bool dummy_flag = false;
	UINT64 start_tick, giveup_tick;
	UINT64 next_send_tick;
	SOCK *s;
	INTERRUPT_MANAGER *interrupt;
	BUF *buf = NULL;
	SOCK_EVENT *se;
	UCHAR *tmp_buf;
	UINT tmp_buf_size = 65535;
	// Validate arguments
	if (cancel == NULL)
	{
		cancel = &dummy_flag;
	}
	if (ip_list == NULL)
	{
		return NULL;
	}

	s = NewUDP6(0, NULL);
	if (s == NULL)
	{
		return NULL;
	}

	tmp_buf = Malloc(tmp_buf_size);

	start_tick = Tick64();
	giveup_tick = start_tick + (UINT64)timeout;
	next_send_tick = 0;

	interrupt = NewInterruptManager();

	AddInterrupt(interrupt, giveup_tick);

	se = NewSockEvent();
	JoinSockToSockEvent(s, se);

	while (true)
	{
		UINT64 now = Tick64();

		if (now >= giveup_tick)
		{
			// Time-out
			break;
		}

		if (*cancel)
		{
			// User canceled
			break;
		}

		// Receive
		while (true)
		{
			IP src_ip;
			UINT src_port;
			UINT r;

			r = RecvFrom(s, &src_ip, &src_port, tmp_buf, tmp_buf_size);

			if (r == SOCK_LATER || r == 0)
			{
				break;
			}

			if (src_port == UDP_FILE_QUERY_DST_PORT)
			{
				if (r >= 40)
				{
					if (Cmp(tmp_buf, UDP_FILE_QUERY_MAGIC_NUMBER, StrLen(UDP_FILE_QUERY_MAGIC_NUMBER)) == 0)
					{
						// Successful reception
						buf = NewBuf();
						WriteBuf(buf, tmp_buf, r);
						SeekBuf(buf, 0, 0);
						break;
					}
				}
			}
		}

		if (buf != NULL)
		{
			// Successful reception
			break;
		}

		if (next_send_tick == 0 || (now >= next_send_tick))
		{
			// Transmission
			UINT i;
			for (i = 0;i < LIST_NUM(ip_list);i++)
			{
				IP *ip = LIST_DATA(ip_list, i);
				UCHAR c = 'F';

				SendTo(s, ip, UDP_FILE_QUERY_DST_PORT, &c, 1);
			}

			next_send_tick = now + (UINT64)UDP_FILE_QUERY_RETRY_INTERVAL;
			AddInterrupt(interrupt, next_send_tick);
		}

		WaitSockEvent(se, GetNextIntervalForInterrupt(interrupt));
	}

	FreeInterruptManager(interrupt);

	Disconnect(s);
	ReleaseSock(s);

	ReleaseSockEvent(se);

	Free(tmp_buf);

	return buf;
}