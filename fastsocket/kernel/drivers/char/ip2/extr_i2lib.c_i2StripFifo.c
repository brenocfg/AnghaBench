#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* i2eBordStrPtr ;
typedef  TYPE_5__* i2ChanStrPtr ;
typedef  TYPE_6__* flowStatPtr ;
typedef  int /*<<< orphan*/  flowStat ;
typedef  int /*<<< orphan*/ * failStatPtr ;
typedef  int /*<<< orphan*/  failStat ;
typedef  int /*<<< orphan*/ * debugStatPtr ;
typedef  int /*<<< orphan*/  debugStat ;
typedef  void** cntStatPtr ;
typedef  int /*<<< orphan*/  cntStat ;
typedef  int /*<<< orphan*/ * bidStatPtr ;
typedef  int /*<<< orphan*/  bidStat ;
struct TYPE_20__ {scalar_t__ asof; scalar_t__ room; } ;
struct TYPE_17__ {int rx; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  dcd; int /*<<< orphan*/  cts; } ;
struct TYPE_16__ {scalar_t__ room; scalar_t__ asof; } ;
struct TYPE_15__ {int /*<<< orphan*/  expires; } ;
struct TYPE_19__ {int hotKeyIn; unsigned short Ibuf_stuff; unsigned char* Ibuf; int dataSetIn; int channelNeeds; int /*<<< orphan*/  tqueue_status; int /*<<< orphan*/  dss_now_wait; TYPE_3__ icount; int /*<<< orphan*/  channelFail; void* channelRcount; void* channelTcount; int /*<<< orphan*/  channelStatus; int /*<<< orphan*/  pTTY; TYPE_2__ outfl; TYPE_1__ BookmarkTimer; int /*<<< orphan*/  pBookmarkWait; int /*<<< orphan*/  bookMarks; int /*<<< orphan*/  tqueue_input; int /*<<< orphan*/  Ibuf_spinlock; } ;
struct TYPE_18__ {int* i2eLeadoffWord; int got_input; int i2eFatal; int i2eChannelCnt; int /*<<< orphan*/  i2eOutMailWaiting; int /*<<< orphan*/  read_fifo_spinlock; int /*<<< orphan*/  channelBtypes; scalar_t__ i2eChannelPtr; } ;

/* Variables and functions */
 int CHANN ; 
 int CHANNEL_OF (int*) ; 
 int CMD_COUNT_OF (int*) ; 
 int /*<<< orphan*/  CMD_HOTACK ; 
 int /*<<< orphan*/  CMD_HW_TEST ; 
 int I2_BRK ; 
 int I2_CTS ; 
 int I2_DCD ; 
 int I2_DCTS ; 
 int I2_DDCD ; 
 int I2_DDSR ; 
 int I2_DRI ; 
 int I2_DSR ; 
 int I2_FRA ; 
 scalar_t__ I2_HAS_INPUT (TYPE_4__*) ; 
 int I2_OVR ; 
 int I2_PAR ; 
 int I2_RI ; 
 unsigned int IBUF_SIZE ; 
 int /*<<< orphan*/  ID_HOT_KEY ; 
 int /*<<< orphan*/  ID_OF (int*) ; 
 int /*<<< orphan*/  ITRC_DRAIN ; 
 int /*<<< orphan*/  ITRC_MODEM ; 
 int ITRC_NO_PORT ; 
 int ITRC_RETURN ; 
 int /*<<< orphan*/  ITRC_SFIFO ; 
 int /*<<< orphan*/  ITRC_STFLW ; 
 int /*<<< orphan*/  MB_IN_STRIPPED ; 
 int NEED_CREDIT ; 
 int /*<<< orphan*/  NEED_INLINE ; 
 int /*<<< orphan*/  PTYPE_BYPASS ; 
#define  PTYPE_DATA 147 
 int /*<<< orphan*/  PTYPE_INLINE ; 
 int PTYPE_OF (int*) ; 
#define  PTYPE_STATUS 146 
#define  STAT_BMARK 145 
#define  STAT_BOXIDS 144 
#define  STAT_BRK_DET 143 
#define  STAT_CTS_DN 142 
#define  STAT_CTS_UP 141 
#define  STAT_DCD_DN 140 
#define  STAT_DCD_UP 139 
#define  STAT_DSR_DN 138 
#define  STAT_DSR_UP 137 
#define  STAT_ERROR 136 
 unsigned char STAT_E_FRAMING ; 
 unsigned char STAT_E_OVERRUN ; 
 unsigned char STAT_E_PARITY ; 
#define  STAT_FLOW 135 
#define  STAT_HWFAIL 134 
#define  STAT_MODEM 133 
 unsigned char STAT_MOD_ERROR ; 
#define  STAT_RI_DN 132 
#define  STAT_RI_UP 131 
#define  STAT_RXCNT 130 
#define  STAT_STATUS 129 
#define  STAT_TXCNT 128 
 unsigned char* cmdBuffer ; 
 int /*<<< orphan*/  do_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2QueueCommands (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2QueueNeeds (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iiReadBuf (TYPE_4__*,unsigned char*,int) ; 
 int iiReadWord (TYPE_4__*) ; 
 int /*<<< orphan*/  ip2_owake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip2trace (int,int /*<<< orphan*/ ,int,int,...) ; 
 unsigned char* junkBuffer ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_baud_params (TYPE_4__*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int* xlatDss ; 

__attribute__((used)) static inline void
i2StripFifo(i2eBordStrPtr pB)
{
	i2ChanStrPtr pCh;
	int channel;
	int count;
	unsigned short stuffIndex;
	int amountToRead;
	unsigned char *pc, *pcLimit;
	unsigned char uc;
	unsigned char dss_change;
	unsigned long bflags,cflags;

//	ip2trace (ITRC_NO_PORT, ITRC_SFIFO, ITRC_ENTER, 0 );

	while (I2_HAS_INPUT(pB)) {
//		ip2trace (ITRC_NO_PORT, ITRC_SFIFO, 2, 0 );

		// Process packet from fifo a one atomic unit
		write_lock_irqsave(&pB->read_fifo_spinlock, bflags);
   
		// The first word (or two bytes) will have channel number and type of
		// packet, possibly other information
		pB->i2eLeadoffWord[0] = iiReadWord(pB);

		switch(PTYPE_OF(pB->i2eLeadoffWord))
		{
		case PTYPE_DATA:
			pB->got_input = 1;

//			ip2trace (ITRC_NO_PORT, ITRC_SFIFO, 3, 0 );

			channel = CHANNEL_OF(pB->i2eLeadoffWord); /* Store channel */
			count = iiReadWord(pB);          /* Count is in the next word */

// NEW: Check the count for sanity! Should the hardware fail, our death
// is more pleasant. While an oversize channel is acceptable (just more
// than the driver supports), an over-length count clearly means we are
// sick!
			if ( ((unsigned int)count) > IBUF_SIZE ) {
				pB->i2eFatal = 2;
				write_unlock_irqrestore(&pB->read_fifo_spinlock,
						bflags);
				return;     /* Bail out ASAP */
			}
			// Channel is illegally big ?
			if ((channel >= pB->i2eChannelCnt) ||
				(NULL==(pCh = ((i2ChanStrPtr*)pB->i2eChannelPtr)[channel])))
			{
				iiReadBuf(pB, junkBuffer, count);
				write_unlock_irqrestore(&pB->read_fifo_spinlock,
						bflags);
				break;         /* From switch: ready for next packet */
			}

			// Channel should be valid, then

			// If this is a hot-key, merely post its receipt for now. These are
			// always supposed to be 1-byte packets, so we won't even check the
			// count. Also we will post an acknowledgement to the board so that
			// more data can be forthcoming. Note that we are not trying to use
			// these sequences in this driver, merely to robustly ignore them.
			if(ID_OF(pB->i2eLeadoffWord) == ID_HOT_KEY)
			{
				pCh->hotKeyIn = iiReadWord(pB) & 0xff;
				write_unlock_irqrestore(&pB->read_fifo_spinlock,
						bflags);
				i2QueueCommands(PTYPE_BYPASS, pCh, 0, 1, CMD_HOTACK);
				break;   /* From the switch: ready for next packet */
			}

			// Normal data! We crudely assume there is room for the data in our
			// buffer because the board wouldn't have exceeded his credit limit.
			write_lock_irqsave(&pCh->Ibuf_spinlock, cflags);
													// We have 2 locks now
			stuffIndex = pCh->Ibuf_stuff;
			amountToRead = IBUF_SIZE - stuffIndex;
			if (amountToRead > count)
				amountToRead = count;

			// stuffIndex would have been already adjusted so there would 
			// always be room for at least one, and count is always at least
			// one.

			iiReadBuf(pB, &(pCh->Ibuf[stuffIndex]), amountToRead);
			pCh->icount.rx += amountToRead;

			// Update the stuffIndex by the amount of data moved. Note we could
			// never ask for more data than would just fit. However, we might
			// have read in one more byte than we wanted because the read
			// rounds up to even bytes. If this byte is on the end of the
			// packet, and is padding, we ignore it. If the byte is part of
			// the actual data, we need to move it.

			stuffIndex += amountToRead;

			if (stuffIndex >= IBUF_SIZE) {
				if ((amountToRead & 1) && (count > amountToRead)) {
					pCh->Ibuf[0] = pCh->Ibuf[IBUF_SIZE];
					amountToRead++;
					stuffIndex = 1;
				} else {
					stuffIndex = 0;
				}
			}

			// If there is anything left over, read it as well
			if (count > amountToRead) {
				amountToRead = count - amountToRead;
				iiReadBuf(pB, &(pCh->Ibuf[stuffIndex]), amountToRead);
				pCh->icount.rx += amountToRead;
				stuffIndex += amountToRead;
			}

			// Update stuff index
			pCh->Ibuf_stuff = stuffIndex;
			write_unlock_irqrestore(&pCh->Ibuf_spinlock, cflags);
			write_unlock_irqrestore(&pB->read_fifo_spinlock,
					bflags);

#ifdef USE_IQ
			schedule_work(&pCh->tqueue_input);
#else
			do_input(&pCh->tqueue_input);
#endif

			// Note we do not need to maintain any flow-control credits at this
			// time:  if we were to increment .asof and decrement .room, there
			// would be no net effect. Instead, when we strip data, we will
			// increment .asof and leave .room unchanged.

			break;   // From switch: ready for next packet

		case PTYPE_STATUS:
			ip2trace (ITRC_NO_PORT, ITRC_SFIFO, 4, 0 );
      
			count = CMD_COUNT_OF(pB->i2eLeadoffWord);

			iiReadBuf(pB, cmdBuffer, count);
			// We can release early with buffer grab
			write_unlock_irqrestore(&pB->read_fifo_spinlock,
					bflags);

			pc = cmdBuffer;
			pcLimit = &(cmdBuffer[count]);

			while (pc < pcLimit) {
				channel = *pc++;

				ip2trace (channel, ITRC_SFIFO, 7, 2, channel, *pc );

				/* check for valid channel */
				if (channel < pB->i2eChannelCnt
					 && 
					 (pCh = (((i2ChanStrPtr*)pB->i2eChannelPtr)[channel])) != NULL
					)
				{
					dss_change = 0;

					switch (uc = *pc++)
					{
					/* Breaks and modem signals are easy: just update status */
					case STAT_CTS_UP:
						if ( !(pCh->dataSetIn & I2_CTS) )
						{
							pCh->dataSetIn |= I2_DCTS;
							pCh->icount.cts++;
							dss_change = 1;
						}
						pCh->dataSetIn |= I2_CTS;
						break;

					case STAT_CTS_DN:
						if ( pCh->dataSetIn & I2_CTS )
						{
							pCh->dataSetIn |= I2_DCTS;
							pCh->icount.cts++;
							dss_change = 1;
						}
						pCh->dataSetIn &= ~I2_CTS;
						break;

					case STAT_DCD_UP:
						ip2trace (channel, ITRC_MODEM, 1, 1, pCh->dataSetIn );

						if ( !(pCh->dataSetIn & I2_DCD) )
						{
							ip2trace (CHANN, ITRC_MODEM, 2, 0 );
							pCh->dataSetIn |= I2_DDCD;
							pCh->icount.dcd++;
							dss_change = 1;
						}
						pCh->dataSetIn |= I2_DCD;

						ip2trace (channel, ITRC_MODEM, 3, 1, pCh->dataSetIn );
						break;

					case STAT_DCD_DN:
						ip2trace (channel, ITRC_MODEM, 4, 1, pCh->dataSetIn );
						if ( pCh->dataSetIn & I2_DCD )
						{
							ip2trace (channel, ITRC_MODEM, 5, 0 );
							pCh->dataSetIn |= I2_DDCD;
							pCh->icount.dcd++;
							dss_change = 1;
						}
						pCh->dataSetIn &= ~I2_DCD;

						ip2trace (channel, ITRC_MODEM, 6, 1, pCh->dataSetIn );
						break;

					case STAT_DSR_UP:
						if ( !(pCh->dataSetIn & I2_DSR) )
						{
							pCh->dataSetIn |= I2_DDSR;
							pCh->icount.dsr++;
							dss_change = 1;
						}
						pCh->dataSetIn |= I2_DSR;
						break;

					case STAT_DSR_DN:
						if ( pCh->dataSetIn & I2_DSR )
						{
							pCh->dataSetIn |= I2_DDSR;
							pCh->icount.dsr++;
							dss_change = 1;
						}
						pCh->dataSetIn &= ~I2_DSR;
						break;

					case STAT_RI_UP:
						if ( !(pCh->dataSetIn & I2_RI) )
						{
							pCh->dataSetIn |= I2_DRI;
							pCh->icount.rng++;
							dss_change = 1;
						}
						pCh->dataSetIn |= I2_RI ;
						break;

					case STAT_RI_DN:
						// to be compat with serial.c
						//if ( pCh->dataSetIn & I2_RI )
						//{
						//	pCh->dataSetIn |= I2_DRI;
						//	pCh->icount.rng++; 
						//	dss_change = 1;
						//}
						pCh->dataSetIn &= ~I2_RI ;
						break;

					case STAT_BRK_DET:
						pCh->dataSetIn |= I2_BRK;
						pCh->icount.brk++;
						dss_change = 1;
						break;

					// Bookmarks? one less request we're waiting for
					case STAT_BMARK:
						pCh->bookMarks--;
						if (pCh->bookMarks <= 0 ) {
							pCh->bookMarks = 0;
							wake_up_interruptible( &pCh->pBookmarkWait );

						ip2trace (channel, ITRC_DRAIN, 20, 1, pCh->BookmarkTimer.expires );
						}
						break;

					// Flow control packets? Update the new credits, and if
					// someone was waiting for output, queue him up again.
					case STAT_FLOW:
						pCh->outfl.room =
							((flowStatPtr)pc)->room -
							(pCh->outfl.asof - ((flowStatPtr)pc)->asof);

						ip2trace (channel, ITRC_STFLW, 1, 1, pCh->outfl.room );

						if (pCh->channelNeeds & NEED_CREDIT)
						{
							ip2trace (channel, ITRC_STFLW, 2, 1, pCh->channelNeeds);

							pCh->channelNeeds &= ~NEED_CREDIT;
							i2QueueNeeds(pB, pCh, NEED_INLINE);
							if ( pCh->pTTY )
								ip2_owake(pCh->pTTY);
						}

						ip2trace (channel, ITRC_STFLW, 3, 1, pCh->channelNeeds);

						pc += sizeof(flowStat);
						break;

					/* Special packets: */
					/* Just copy the information into the channel structure */

					case STAT_STATUS:

						pCh->channelStatus = *((debugStatPtr)pc);
						pc += sizeof(debugStat);
						break;

					case STAT_TXCNT:

						pCh->channelTcount = *((cntStatPtr)pc);
						pc += sizeof(cntStat);
						break;

					case STAT_RXCNT:

						pCh->channelRcount = *((cntStatPtr)pc);
						pc += sizeof(cntStat);
						break;

					case STAT_BOXIDS:
						pB->channelBtypes = *((bidStatPtr)pc);
						pc += sizeof(bidStat);
						set_baud_params(pB);
						break;

					case STAT_HWFAIL:
						i2QueueCommands (PTYPE_INLINE, pCh, 0, 1, CMD_HW_TEST);
						pCh->channelFail = *((failStatPtr)pc);
						pc += sizeof(failStat);
						break;

					/* No explicit match? then
					 * Might be an error packet...
					 */
					default:
						switch (uc & STAT_MOD_ERROR)
						{
						case STAT_ERROR:
							if (uc & STAT_E_PARITY) {
								pCh->dataSetIn |= I2_PAR;
								pCh->icount.parity++;
							}
							if (uc & STAT_E_FRAMING){
								pCh->dataSetIn |= I2_FRA;
								pCh->icount.frame++;
							}
							if (uc & STAT_E_OVERRUN){
								pCh->dataSetIn |= I2_OVR;
								pCh->icount.overrun++;
							}
							break;

						case STAT_MODEM:
							// the answer to DSS_NOW request (not change)
							pCh->dataSetIn = (pCh->dataSetIn
								& ~(I2_RI | I2_CTS | I2_DCD | I2_DSR) )
								| xlatDss[uc & 0xf];
							wake_up_interruptible ( &pCh->dss_now_wait );
						default:
							break;
						}
					}  /* End of switch on status type */
					if (dss_change) {
#ifdef USE_IQ
						schedule_work(&pCh->tqueue_status);
#else
						do_status(&pCh->tqueue_status);
#endif
					}
				}
				else  /* Or else, channel is invalid */
				{
					// Even though the channel is invalid, we must test the
					// status to see how much additional data it has (to be
					// skipped)
					switch (*pc++)
					{
					case STAT_FLOW:
						pc += 4;    /* Skip the data */
						break;

					default:
						break;
					}
				}
			}  // End of while (there is still some status packet left)
			break;

		default: // Neither packet? should be impossible
			ip2trace (ITRC_NO_PORT, ITRC_SFIFO, 5, 1,
				PTYPE_OF(pB->i2eLeadoffWord) );
			write_unlock_irqrestore(&pB->read_fifo_spinlock,
					bflags);

			break;
		}  // End of switch on type of packets
	}	/*while(board I2_HAS_INPUT)*/

	ip2trace (ITRC_NO_PORT, ITRC_SFIFO, ITRC_RETURN, 0 );

	// Send acknowledgement to the board even if there was no data!
	pB->i2eOutMailWaiting |= MB_IN_STRIPPED;
	return;
}