#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
typedef  int /*<<< orphan*/  i2CmdHeader ;
typedef  TYPE_2__* i2ChanStrPtr ;
struct TYPE_10__ {unsigned short Cbuf_strip; unsigned short Cbuf_stuff; unsigned char* Cbuf; int /*<<< orphan*/  Cbuf_spinlock; } ;
struct TYPE_9__ {int /*<<< orphan*/  debugBypassCount; } ;

/* Variables and functions */
 unsigned short CBUF_SIZE ; 
 int CMD_COUNT_OF (unsigned char*) ; 
 int /*<<< orphan*/  ITRC_ERROR ; 
 int /*<<< orphan*/  ITRC_NO_PORT ; 
 int /*<<< orphan*/  NEED_BYPASS ; 
 int /*<<< orphan*/  WriteDBGBuf (char*,unsigned char*,unsigned short) ; 
 TYPE_2__* i2DeQueueNeeds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2QueueNeeds (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2Write2Fifo (TYPE_1__*,unsigned char*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned short roundup (unsigned short,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
i2StuffFifoBypass(i2eBordStrPtr pB)
{
	i2ChanStrPtr pCh;
	unsigned char *pRemove;
	unsigned short stripIndex;
	unsigned short packetSize;
	unsigned short paddedSize;
	unsigned short notClogged = 1;
	unsigned long flags;

	int bailout = 1000;

	// Continue processing so long as there are entries, or there is room in the
	// fifo. Each entry represents a channel with something to do.
	while ( --bailout && notClogged && 
			(NULL != (pCh = i2DeQueueNeeds(pB,NEED_BYPASS))))
	{
		write_lock_irqsave(&pCh->Cbuf_spinlock, flags);
		stripIndex = pCh->Cbuf_strip;

		// as long as there are packets for this channel...

		while (stripIndex != pCh->Cbuf_stuff) {
			pRemove = &(pCh->Cbuf[stripIndex]);
			packetSize = CMD_COUNT_OF(pRemove) + sizeof(i2CmdHeader);
			paddedSize = roundup(packetSize, 2);

			if (paddedSize > 0) {
				if ( 0 == i2Write2Fifo(pB, pRemove, paddedSize,0)) {
					notClogged = 0;	/* fifo full */
					i2QueueNeeds(pB, pCh, NEED_BYPASS);	// Put back on queue
					break;   // Break from the channel
				} 
			}
#ifdef DEBUG_FIFO
WriteDBGBuf("BYPS", pRemove, paddedSize);
#endif	/* DEBUG_FIFO */
			pB->debugBypassCount++;

			pRemove += packetSize;
			stripIndex += packetSize;
			if (stripIndex >= CBUF_SIZE) {
				stripIndex = 0;
				pRemove = pCh->Cbuf;
			}
		}
		// Done with this channel. Move to next, removing this one from 
		// the queue of channels if we cleaned it out (i.e., didn't get clogged.
		pCh->Cbuf_strip = stripIndex;
		write_unlock_irqrestore(&pCh->Cbuf_spinlock, flags);
	}  // Either clogged or finished all the work

#ifdef IP2DEBUG_TRACE
	if ( !bailout ) {
		ip2trace (ITRC_NO_PORT, ITRC_ERROR, 1, 0 );
	}
#endif
}