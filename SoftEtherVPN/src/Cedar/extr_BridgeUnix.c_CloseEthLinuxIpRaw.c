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
struct TYPE_4__ {struct TYPE_4__* RawIP_TmpBuffer; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  RawIcmp; int /*<<< orphan*/  RawUdp; int /*<<< orphan*/  RawTcp; struct TYPE_4__* Title; struct TYPE_4__* Name; int /*<<< orphan*/  RawIpSendQueue; } ;
typedef  TYPE_1__ ETH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 

void CloseEthLinuxIpRaw(ETH *e)
{
	if (e == NULL)
	{
		return;
	}

	while (true)
	{
		BUF *buf = GetNext(e->RawIpSendQueue);
		if (buf == NULL)
		{
			break;
		}

		FreeBuf(buf);
	}
	ReleaseQueue(e->RawIpSendQueue);

	Free(e->Name);
	Free(e->Title);

	ReleaseSock(e->RawTcp);
	ReleaseSock(e->RawUdp);
	ReleaseSock(e->RawIcmp);

	ReleaseCancel(e->Cancel);

	Free(e->RawIP_TmpBuffer);

	Free(e);
}