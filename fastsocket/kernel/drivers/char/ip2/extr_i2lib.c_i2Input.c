#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* i2ChanStrPtr ;
struct TYPE_14__ {int receive_room; TYPE_2__* ldisc; } ;
struct TYPE_12__ {int asof; } ;
struct TYPE_13__ {unsigned short Ibuf_strip; unsigned short Ibuf_stuff; int sinceLastFlow; int whenSendFlow; int /*<<< orphan*/  Ibuf_spinlock; int /*<<< orphan*/  pMyBord; TYPE_3__ infl; int /*<<< orphan*/ * Ibuf; TYPE_5__* pTTY; } ;
struct TYPE_11__ {TYPE_1__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* receive_buf ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int IBUF_SIZE ; 
 int /*<<< orphan*/  ITRC_ENTER ; 
 int /*<<< orphan*/  ITRC_INPUT ; 
 int /*<<< orphan*/  ITRC_RETURN ; 
 int /*<<< orphan*/  NEED_FLOW ; 
 int /*<<< orphan*/  i2QueueNeeds (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2Validate (TYPE_4__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
i2Input(i2ChanStrPtr pCh)
{
	int amountToMove;
	unsigned short stripIndex;
	int count;
	unsigned long flags = 0;

	ip2trace (CHANN, ITRC_INPUT, ITRC_ENTER, 0);

	// Ensure channel structure seems real
	if ( !i2Validate( pCh ) ) {
		count = -1;
		goto i2Input_exit;
	}
	write_lock_irqsave(&pCh->Ibuf_spinlock, flags);

	// initialize some accelerators and private copies
	stripIndex = pCh->Ibuf_strip;

	count = pCh->Ibuf_stuff - stripIndex;

	// If buffer is empty or requested data count was 0, (trivial case) return
	// without any further thought.
	if ( count == 0 ) {
		write_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
		goto i2Input_exit;
	}
	// Adjust for buffer wrap
	if ( count < 0 ) {
		count += IBUF_SIZE;
	}
	// Don't give more than can be taken by the line discipline
	amountToMove = pCh->pTTY->receive_room;
	if (count > amountToMove) {
		count = amountToMove;
	}
	// How much could we copy without a wrap?
	amountToMove = IBUF_SIZE - stripIndex;

	if (amountToMove > count) {
		amountToMove = count;
	}
	// Move the first block
	pCh->pTTY->ldisc->ops->receive_buf( pCh->pTTY,
		 &(pCh->Ibuf[stripIndex]), NULL, amountToMove );
	// If we needed to wrap, do the second data move
	if (count > amountToMove) {
		pCh->pTTY->ldisc->ops->receive_buf( pCh->pTTY,
		 pCh->Ibuf, NULL, count - amountToMove );
	}
	// Bump and wrap the stripIndex all at once by the amount of data read. This
	// method is good regardless of whether the data was in one or two pieces.
	stripIndex += count;
	if (stripIndex >= IBUF_SIZE) {
		stripIndex -= IBUF_SIZE;
	}
	pCh->Ibuf_strip = stripIndex;

	// Update our flow control information and possibly queue ourselves to send
	// it, depending on how much data has been stripped since the last time a
	// packet was sent.
	pCh->infl.asof += count;

	if ((pCh->sinceLastFlow += count) >= pCh->whenSendFlow) {
		pCh->sinceLastFlow -= pCh->whenSendFlow;
		write_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
		i2QueueNeeds(pCh->pMyBord, pCh, NEED_FLOW);
	} else {
		write_unlock_irqrestore(&pCh->Ibuf_spinlock, flags);
	}

i2Input_exit:

	ip2trace (CHANN, ITRC_INPUT, ITRC_RETURN, 1, count);

	return count;
}