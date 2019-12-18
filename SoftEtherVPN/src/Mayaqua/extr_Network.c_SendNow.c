#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_5__ {int AsyncMode; TYPE_4__* SendBuf; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBuf (TYPE_4__*) ; 
 int SendAll (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

bool SendNow(SOCK *sock, int secure)
{
	bool ret;
	// Validate arguments
	if (sock == NULL || sock->AsyncMode != false)
	{
		return false;
	}
	if (sock->SendBuf->Size == 0)
	{
		return true;
	}

	ret = SendAll(sock, sock->SendBuf->Buf, sock->SendBuf->Size, secure);
	ClearBuf(sock->SendBuf);

	return ret;
}