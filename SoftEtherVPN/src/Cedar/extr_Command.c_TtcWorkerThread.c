#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp64 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  suprise ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_7__ {int AbnormalTerminated; scalar_t__ end_tick; scalar_t__ RealSpan; scalar_t__ start_tick; scalar_t__* Cancel; scalar_t__ Halt; int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; void* ErrorCode; scalar_t__ Span; scalar_t__ session_id; int /*<<< orphan*/  flag2; int /*<<< orphan*/  flag1; } ;
struct TYPE_6__ {int Download; int ServerUploadReportReceived; int State; scalar_t__ NextSendRequestReportTick; int HideErrMsg; double Id; int /*<<< orphan*/  NumBytes; int /*<<< orphan*/  Sock; } ;
struct TYPE_5__ {int Ok; int /*<<< orphan*/  SockList; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  StartEvent; TYPE_3__* Ttc; } ;
typedef  TYPE_1__ TTC_WORKER ;
typedef  TYPE_2__ TTC_SOCK ;
typedef  TYPE_3__ TTC ;
typedef  int /*<<< orphan*/  THREAD ;

/* Variables and functions */
 void* ERR_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  Endian64 (scalar_t__) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 scalar_t__ Recv (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ Send (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  TtGenerateRandomData (scalar_t__**,scalar_t__*) ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  WRITE_UINT64 (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void TtcWorkerThread(THREAD *thread, void *param)
{
	TTC_WORKER *w;
	TTC *ttc;
	bool dont_block_next_time = false;
	bool halting = false;
	UINT64 halt_timeout = 0;
	bool all_sockets_blocked;
	wchar_t tmp[MAX_SIZE];
	UCHAR *send_buf_data, *recv_buf_data;
	UINT buf_size;
	UINT64 tmp64;

	if (thread == NULL || param == NULL)
	{
		return;
	}

	w = (TTC_WORKER *)param;
	ttc = w->Ttc;

	// Allocate the data area
	TtGenerateRandomData(&send_buf_data, &buf_size);
	TtGenerateRandomData(&recv_buf_data, &buf_size);

	NoticeThreadInit(thread);

	// Wait for start
	Wait(w->StartEvent, INFINITE);

	// Main loop
	while (true)
	{
		UINT i;

		if (dont_block_next_time == false)
		{
			WaitSockEvent(w->SockEvent, 50);
		}

		dont_block_next_time = false;

		if (ttc->AbnormalTerminated)
		{
			// Abnormal termination occured
			break;
		}

		if (ttc->Halt || ttc->end_tick <= Tick64() || (ttc->Cancel != NULL && (*ttc->Cancel)))
		{
			// End measurement
			if (halting == false)
			{
				if (ttc->Halt || (ttc->Cancel != NULL && (*ttc->Cancel)))
				{
					if ((ttc->flag1++) == 0)
					{
						// User cancel
						TtPrint(ttc->Param, ttc->Print, _UU("TTC_COMM_USER_CANCEL"));
					}
				}
				else
				{
					// Time elapsed
					if ((ttc->flag2++) == 0)
					{
						UniFormat(tmp, sizeof(tmp), _UU("TTC_COMM_END"),
							(double)ttc->Span / 1000.0);
						TtPrint(ttc->Param, ttc->Print, tmp);
					}
				}

				if (ttc->RealSpan == 0)
				{
					ttc->RealSpan = Tick64() - ttc->start_tick;
				}

				halting = true;

				// Wait for reporting data from the server
				halt_timeout = Tick64() + 60000ULL;
			}
		}

		if (halt_timeout != 0)
		{
			bool ok = true;

			// Wait that all TCP connections to finish processing
			for (i = 0;i < LIST_NUM(w->SockList);i++)
			{
				TTC_SOCK *ts = LIST_DATA(w->SockList, i);

				if (ts->Download == false)
				{
					if (ts->ServerUploadReportReceived == false)
					{
						ok = false;
					}
				}
			}

			if (ok)
			{
				// Measurement completed
				w->Ok = true;
				break;
			}
			else
			{
				if (halt_timeout <= Tick64())
				{
					// An error occured
					ttc->AbnormalTerminated = true;
					ttc->ErrorCode = ERR_PROTOCOL_ERROR;
					break;
				}
			}
		}

		all_sockets_blocked = false;

		// Continue to send and receive data
		// until all sockets become block state
		while (all_sockets_blocked == false)
		{
			all_sockets_blocked = true;

			for (i = 0;i < LIST_NUM(w->SockList);i++)
			{
				UINT ret = SOCK_LATER;
				TTC_SOCK *ts = LIST_DATA(w->SockList, i);
				bool blocked_for_this_socket = false;
				UCHAR c = 0;
				UCHAR c_and_session_id[1 + sizeof(UINT64) + sizeof(UINT64)];

				if (halt_timeout != 0)
				{
					if (ts->State != 3 && ts->State != 4)
					{
						if (ts->Download == false)
						{
							if (ts->State != 0)
							{
								ts->State = 3;
							}
							else
							{
								ts->ServerUploadReportReceived = true;
								ts->State = 4;
							}
						}
						else
						{
							ts->State = 4;
						}
					}
				}

				switch (ts->State)
				{
				case 0:
					// Initial state: Specify the direction of
					// the data flow between client-server
					if (ts->Download)
					{
						c = 1;
					}
					else
					{
						c = 0;
					}

					c_and_session_id[0] = c;
					WRITE_UINT64(c_and_session_id + 1, ttc->session_id);
					WRITE_UINT64(c_and_session_id + sizeof(UINT64) + 1, ttc->Span);

					ret = Send(ts->Sock, c_and_session_id, 1 + sizeof(UINT64) + sizeof(UINT64), false);

					if (ret != 0 && ret != SOCK_LATER)
					{
						if (ts->Download)
						{
							ts->State = 1;
						}
						else
						{
							ts->State = 2;
						}
					}
					break;

				case 1:
					// Server -> Client (download)
					ret = Recv(ts->Sock, recv_buf_data, buf_size, false);
					break;

				case 2:
					// Client -> Server (upload)
					ret = Send(ts->Sock, send_buf_data, buf_size, false);
					break;

				case 3:
					// Transmission completion client -> server (upload)
					// Request the data size
					if (ts->NextSendRequestReportTick == 0 ||
						(Tick64() >= ts->NextSendRequestReportTick))
					{
						UCHAR suprise[MAX_SIZE];
						UINT i;

						ts->NextSendRequestReportTick = Tick64() + 200ULL;

						for (i = 0;i < sizeof(suprise);i++)
						{
							suprise[i] = '!';
						}

						(void)Send(ts->Sock, suprise, sizeof(suprise), false);
					}

					ret = Recv(ts->Sock, &tmp64, sizeof(tmp64), false);
					if (ret != 0 && ret != SOCK_LATER && ret == sizeof(tmp64))
					{
						ts->NumBytes = Endian64(tmp64);

						ts->ServerUploadReportReceived = true;

						ts->State = 4;
					}
					break;

				case 4:
					// Do Nothing
					if (Recv(ts->Sock, recv_buf_data, buf_size, false) == SOCK_LATER)
					{
						ret = SOCK_LATER;
					}
					break;
				}

				if (ret == 0)
				{
					// The socket is disconnected
					ttc->AbnormalTerminated = true;
					ttc->ErrorCode = ERR_PROTOCOL_ERROR;
					blocked_for_this_socket = true;
					dont_block_next_time = false;

					if (ts->HideErrMsg == false)
					{
						UniFormat(tmp, sizeof(tmp), _UU("TTC_COMM_DISCONNECTED"), ts->Id);
						TtPrint(ttc->Param, ttc->Print, tmp);
						ts->HideErrMsg = true;
					}
				}
				else if (ret == SOCK_LATER)
				{
					// Delay has occurred
					blocked_for_this_socket = true;
					dont_block_next_time = false;
				}
				else
				{
					if (ts->Download)
					{
						ts->NumBytes += (UINT64)ret;
					}
				}

				if (blocked_for_this_socket == false)
				{
					all_sockets_blocked = false;
				}
			}

			if (ttc->Halt || (ttc->Cancel != NULL && (*ttc->Cancel)))
			{
				all_sockets_blocked = true;
				dont_block_next_time = true;
			}

			if (ttc->end_tick <= Tick64())
			{
				all_sockets_blocked = true;
				dont_block_next_time = true;
			}
		}
	}

	Free(send_buf_data);
	Free(recv_buf_data);
}