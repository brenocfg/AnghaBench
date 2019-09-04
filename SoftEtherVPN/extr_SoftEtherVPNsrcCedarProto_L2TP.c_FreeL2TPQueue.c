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
struct TYPE_4__ {int /*<<< orphan*/  L2TPPacket; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ L2TP_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeL2TPPacket (int /*<<< orphan*/ ) ; 

void FreeL2TPQueue(L2TP_QUEUE *q)
{
	// Validate arguments
	if (q == NULL)
	{
		return;
	}

	FreeBuf(q->Buf);

	FreeL2TPPacket(q->L2TPPacket);

	Free(q);
}