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
typedef  TYPE_2__* i2ChanStrPtr ;
struct TYPE_6__ {int asof; } ;
struct TYPE_7__ {int Ibuf_stuff; int Ibuf_strip; int sinceLastFlow; int whenSendFlow; int /*<<< orphan*/  Ibuf_spinlock; int /*<<< orphan*/  pMyBord; TYPE_1__ infl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 scalar_t__ IBUF_SIZE ; 
 int /*<<< orphan*/  ITRC_INPUT ; 
 int /*<<< orphan*/  NEED_FLOW ; 
 int /*<<< orphan*/  i2QueueNeeds (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2Validate (TYPE_2__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
i2InputFlush(i2ChanStrPtr pCh)
{
	int count;
	unsigned long flags;

	// Ensure channel structure seems real
	if ( !i2Validate ( pCh ) )
		return -1;

	ip2trace (CHANN, ITRC_INPUT, 10, 0);

	write_lock_irqsave(&pCh->Ibuf_spinlock, flags);
	count = pCh->Ibuf_stuff - pCh->Ibuf_strip;

	// Adjust for buffer wrap
	if (count < 0) {
		count += IBUF_SIZE;
	}

	// Expedient way to zero out the buffer
	pCh->Ibuf_strip = pCh->Ibuf_stuff;


	// Update our flow control information and possibly queue ourselves to send
	// it, depending on how much data has been stripped since the last time a
	// packet was sent.

	pCh->infl.asof += count;

	if ( (pCh->sinceLastFlow += count) >= pCh->whenSendFlow )
	{
		pCh->sinceLastFlow -= pCh->whenSendFlow;
		write_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
		i2QueueNeeds(pCh->pMyBord, pCh, NEED_FLOW);
	} else {
		write_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
	}

	ip2trace (CHANN, ITRC_INPUT, 19, 1, count);

	return count;
}