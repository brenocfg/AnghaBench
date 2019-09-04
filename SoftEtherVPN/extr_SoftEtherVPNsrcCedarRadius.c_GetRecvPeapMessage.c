#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_14__ {TYPE_1__* SslPipe; } ;
struct TYPE_13__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Len; } ;
struct TYPE_12__ {int /*<<< orphan*/  RecvFifo; } ;
struct TYPE_11__ {TYPE_2__* SslInOut; } ;
typedef  TYPE_3__ EAP_MESSAGE ;
typedef  TYPE_4__ EAP_CLIENT ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endian16 (int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 TYPE_5__* ReadFifoAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

bool GetRecvPeapMessage(EAP_CLIENT *e, EAP_MESSAGE *msg)
{
	BUF *b;
	bool ret = false;
	if (e == NULL)
	{
		return false;
	}
	if (e->SslPipe == NULL)
	{
		return false;
	}

	b = ReadFifoAll(e->SslPipe->SslInOut->RecvFifo);

	if (b->Size >= 1)
	{
		Zero(msg, sizeof(EAP_MESSAGE));

		msg->Len = Endian16(b->Size + 4);
		Copy(&msg->Type, b->Buf, MIN(b->Size, 1501));

		ret = true;
	}

	FreeBuf(b);

	return ret;
}