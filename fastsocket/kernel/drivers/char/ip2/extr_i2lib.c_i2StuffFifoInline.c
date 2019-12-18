#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* i2eBordStrPtr ;
typedef  int /*<<< orphan*/  i2DataHeader ;
typedef  int /*<<< orphan*/  i2CmdHeader ;
typedef  TYPE_4__* i2ChanStrPtr ;
struct TYPE_12__ {unsigned short room; unsigned short asof; } ;
struct TYPE_11__ {unsigned short tx; } ;
struct TYPE_14__ {unsigned short Obuf_strip; unsigned short Obuf_stuff; unsigned char* Obuf; unsigned short Obuf_char_count; scalar_t__ pTTY; int /*<<< orphan*/  Obuf_spinlock; TYPE_2__ outfl; TYPE_1__ icount; } ;
struct TYPE_13__ {unsigned short i2Dbuf_strip; int /*<<< orphan*/  debugInlineCount; int /*<<< orphan*/  i2eFifoRemains; int /*<<< orphan*/  i2Dbuf_stuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 unsigned short CMD_COUNT_OF (unsigned char*) ; 
 unsigned short CREDIT_USAGE (unsigned short) ; 
 unsigned short DATA_COUNT_OF (unsigned char*) ; 
 int /*<<< orphan*/  ITRC_ENTER ; 
 int /*<<< orphan*/  ITRC_ERROR ; 
 int /*<<< orphan*/  ITRC_NO_PORT ; 
 int ITRC_RETURN ; 
 int /*<<< orphan*/  ITRC_SICMD ; 
 int /*<<< orphan*/  NEED_CREDIT ; 
 int /*<<< orphan*/  NEED_INLINE ; 
 unsigned short OBUF_SIZE ; 
 scalar_t__ PTYPE_DATA ; 
 scalar_t__ PTYPE_OF (unsigned char*) ; 
 int /*<<< orphan*/  WriteDBGBuf (char*,unsigned char*,unsigned short) ; 
 TYPE_4__* i2DeQueueNeeds (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2QueueNeeds (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2Write2Fifo (TYPE_3__*,unsigned char*,unsigned short,int) ; 
 int /*<<< orphan*/  ip2_owake (scalar_t__) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 unsigned short roundup (unsigned short,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
i2StuffFifoInline(i2eBordStrPtr pB)
{
	i2ChanStrPtr pCh;
	unsigned char *pRemove;
	unsigned short stripIndex;
	unsigned short packetSize;
	unsigned short paddedSize;
	unsigned short notClogged = 1;
	unsigned short flowsize;
	unsigned long flags;

	int bailout  = 1000;
	int bailout2;

	ip2trace (ITRC_NO_PORT, ITRC_SICMD, ITRC_ENTER, 3, pB->i2eFifoRemains, 
			pB->i2Dbuf_strip, pB->i2Dbuf_stuff );

	// Continue processing so long as there are entries, or there is room in the
	// fifo. Each entry represents a channel with something to do.
	while ( --bailout && notClogged && 
			(NULL != (pCh = i2DeQueueNeeds(pB,NEED_INLINE))) )
	{
		write_lock_irqsave(&pCh->Obuf_spinlock, flags);
		stripIndex = pCh->Obuf_strip;

		ip2trace (CHANN, ITRC_SICMD, 3, 2, stripIndex, pCh->Obuf_stuff );

		// as long as there are packets for this channel...
		bailout2 = 1000;
		while ( --bailout2 && stripIndex != pCh->Obuf_stuff) {
			pRemove = &(pCh->Obuf[stripIndex]);

			// Must determine whether this be a data or command packet to
			// calculate correctly the header size and the amount of
			// flow-control credit this type of packet will use.
			if (PTYPE_OF(pRemove) == PTYPE_DATA) {
				flowsize = DATA_COUNT_OF(pRemove);
				packetSize = flowsize + sizeof(i2DataHeader);
			} else {
				flowsize = CMD_COUNT_OF(pRemove);
				packetSize = flowsize + sizeof(i2CmdHeader);
			}
			flowsize = CREDIT_USAGE(flowsize);
			paddedSize = roundup(packetSize, 2);

			ip2trace (CHANN, ITRC_SICMD, 4, 2, pB->i2eFifoRemains, paddedSize );

			// If we don't have enough credits from the board to send the data,
			// flag the channel that we are waiting for flow control credit, and
			// break out. This will clean up this channel and remove us from the
			// queue of hot things to do.

				ip2trace (CHANN, ITRC_SICMD, 5, 2, pCh->outfl.room, flowsize );

			if (pCh->outfl.room <= flowsize)	{
				// Do Not have the credits to send this packet.
				i2QueueNeeds(pB, pCh, NEED_CREDIT);
				notClogged = 0;
				break;   // So to do next channel
			}
			if ( (paddedSize > 0) 
				&& ( 0 == i2Write2Fifo(pB, pRemove, paddedSize, 128))) {
				// Do Not have room in fifo to send this packet.
				notClogged = 0;
				i2QueueNeeds(pB, pCh, NEED_INLINE);	
				break;   // Break from the channel
			}
#ifdef DEBUG_FIFO
WriteDBGBuf("DATA", pRemove, paddedSize);
#endif /* DEBUG_FIFO */
			pB->debugInlineCount++;

			pCh->icount.tx += flowsize;
			// Update current credits
			pCh->outfl.room -= flowsize;
			pCh->outfl.asof += flowsize;
			if (PTYPE_OF(pRemove) == PTYPE_DATA) {
				pCh->Obuf_char_count -= DATA_COUNT_OF(pRemove);
			}
			pRemove += packetSize;
			stripIndex += packetSize;

			ip2trace (CHANN, ITRC_SICMD, 6, 2, stripIndex, pCh->Obuf_strip);

			if (stripIndex >= OBUF_SIZE) {
				stripIndex = 0;
				pRemove = pCh->Obuf;

				ip2trace (CHANN, ITRC_SICMD, 7, 1, stripIndex );

			}
		}	/* while */
		if ( !bailout2 ) {
			ip2trace (CHANN, ITRC_ERROR, 3, 0 );
		}
		// Done with this channel. Move to next, removing this one from the
		// queue of channels if we cleaned it out (i.e., didn't get clogged.
		pCh->Obuf_strip = stripIndex;
		write_unlock_irqrestore(&pCh->Obuf_spinlock, flags);
		if ( notClogged )
		{

			ip2trace (CHANN, ITRC_SICMD, 8, 0 );

			if ( pCh->pTTY ) {
				ip2_owake(pCh->pTTY);
			}
		}
	}  // Either clogged or finished all the work

	if ( !bailout ) {
		ip2trace (ITRC_NO_PORT, ITRC_ERROR, 4, 0 );
	}

	ip2trace (ITRC_NO_PORT, ITRC_SICMD, ITRC_RETURN, 1,pB->i2Dbuf_strip);
}