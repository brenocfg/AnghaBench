#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zero ;
typedef  int /*<<< orphan*/  tmp ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  WSAEVENT ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  OsType; } ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FD_CONNECT ; 
 int /*<<< orphan*/  FIONBIO ; 
 TYPE_1__* GetOsInfo () ; 
 scalar_t__ INVALID_SOCKET ; 
 int OS_IS_WINDOWS_NT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int TIMEOUT_TCP_PORT_CHECK ; 
 scalar_t__ Tick64 () ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 int WSAEALREADY ; 
 int WSAEINVAL ; 
 int WSAEISCONN ; 
 int WSAEWOULDBLOCK ; 
 int /*<<< orphan*/  WSAEventSelect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  WSAIoctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int connect (scalar_t__,struct sockaddr*,int) ; 

int connect_timeout(SOCKET s, struct sockaddr *addr, int size, int timeout, bool *cancel_flag)
{
	UINT64 start_time;
	bool ok = false;
	bool timeouted = false;
	WSAEVENT hEvent;
	UINT zero = 0;
	UINT tmp = 0;
	UINT ret_size = 0;
	bool is_nt = false;
	// Validate arguments
	if (s == INVALID_SOCKET || addr == NULL)
	{
		return -1;
	}
	if (timeout == 0)
	{
		timeout = TIMEOUT_TCP_PORT_CHECK;
	}

	is_nt = OS_IS_WINDOWS_NT(GetOsInfo()->OsType);

	// Create an event
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	// Associate the socket with the event
	WSAEventSelect(s, hEvent, FD_CONNECT);

	start_time = Tick64();

	while (true)
	{
		int ret;
		
		ret = connect(s, addr, size);

		if (ret == 0)
		{
			ok = true;
			break;
		}
		else
		{
			int err = WSAGetLastError();
			//Debug("err=%u\n", err);
			//Debug("cancel_flag=%u\n", *cancel_flag);
			if (timeouted && ((err == WSAEALREADY) || (err == WSAEWOULDBLOCK && !is_nt)))
			{
				// Time-out
				ok = false;
				break;
			}
			if (*cancel_flag)
			{
				// Cancel
				ok = false;
				break;
			}
			if (err == WSAEISCONN || (err == WSAEINVAL && is_nt))
			{
				ok = true;
				break;
			}
			if (((start_time + (UINT64)timeout) <= Tick64()) || (err != WSAEWOULDBLOCK && err != WSAEALREADY && (is_nt || err != WSAEINVAL)))
			{
				// Failure (timeout)
				break;
			}
			else
			{
				SleepThread(10);
				// Connecting
				if (WaitForSingleObject(hEvent, 100) == WAIT_OBJECT_0)
				{
					timeouted = true;
				}
			}
		}
	}

	// Remove the socket from the event
	WSAEventSelect(s, hEvent, 0);

	// Restore to synchronized socket
	WSAIoctl(s, FIONBIO, &zero, sizeof(zero), &tmp, sizeof(tmp), &ret_size, NULL, NULL);

	// Close the event
	CloseHandle(hEvent);

	if (ok)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}