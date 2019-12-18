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
 scalar_t__ Send (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int) ; 

bool SendAll(SOCK *sock, void *data, UINT size, bool secure)
{
	UCHAR *buf;
	UINT sent_size;
	UINT ret;
	// Validate arguments
	if (sock == NULL || data == NULL)
	{
		return false;
	}
	if (sock->AsyncMode)
	{
		return false;
	}
	if (size == 0)
	{
		return true;
	}

	buf = (UCHAR *)data;
	sent_size = 0;

	while (true)
	{
		ret = Send(sock, buf, size - sent_size, secure);
		if (ret == 0)
		{
			return false;
		}
		sent_size += ret;
		buf += ret;
		if (sent_size >= size)
		{
			return true;
		}
	}
}