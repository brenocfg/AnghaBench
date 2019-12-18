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
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  TubeSend; int /*<<< orphan*/  FlushList; } ;
typedef  TYPE_1__ PPP_SESSION ;
typedef  int /*<<< orphan*/  PPP_PACKET ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddTubeToFlushList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* BuildPPPPacketData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int TubeSendEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

bool PPPSendPacketEx(PPP_SESSION *p, PPP_PACKET *pp, bool no_flush)
{
	bool ret = false;
	BUF *b;
	// Validate arguments
	if (p == NULL || pp == NULL)
	{
		return false;
	}

	b = BuildPPPPacketData(pp);
	if (b == NULL)
	{
		return false;
	}

	ret = TubeSendEx(p->TubeSend, b->Buf, b->Size, NULL, no_flush);

	if (no_flush)
	{
		AddTubeToFlushList(p->FlushList, p->TubeSend);
	}

	FreeBuf(b);

	return ret;
}