#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {scalar_t__ AsyncMode; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 scalar_t__ Recv (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ SOCK_LATER ; 

bool RecvAll(SOCK *sock, void *data, UINT size, bool secure)
{
	UINT recv_size, sz, ret;
	// Validate arguments
	if (sock == NULL || data == NULL)
	{
		return false;
	}
	if (size == 0)
	{
		return true;
	}
	if (sock->AsyncMode)
	{
		return false;
	}

	recv_size = 0;

	while (true)
	{
		sz = size - recv_size;
		ret = Recv(sock, (UCHAR *)data + recv_size, sz, secure);
		if (ret == 0)
		{
			return false;
		}
		if (ret == SOCK_LATER)
		{
			// I suppose that this is safe because the RecvAll() function is used only 
			// if the sock->AsyncMode == true. And the Recv() function may return
			// SOCK_LATER only if the sock->AsyncMode == false. Therefore the call of 
			// Recv() function in the RecvAll() function never returns SOCK_LATER.
			return false;
		}
		recv_size += ret;
		if (recv_size >= size)
		{
			return true;
		}
	}
}