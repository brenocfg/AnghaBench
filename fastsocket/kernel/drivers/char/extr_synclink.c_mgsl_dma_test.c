#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mgsl_struct {int /*<<< orphan*/  params; int /*<<< orphan*/  irq_spinlock; TYPE_1__* rx_buffer_list; TYPE_2__* tx_buffer_list; } ;
struct TYPE_4__ {unsigned int count; unsigned int rcc; int status; char* virt_addr; unsigned long phys_entry; } ;
struct TYPE_3__ {unsigned short status; unsigned int count; unsigned long phys_entry; int /*<<< orphan*/  virt_addr; } ;
typedef  int /*<<< orphan*/  MGSL_PARAMS ;

/* Variables and functions */
 unsigned short BIT1 ; 
 unsigned short BIT2 ; 
 unsigned short BIT3 ; 
 unsigned short BIT4 ; 
 unsigned short BIT5 ; 
 unsigned short BIT6 ; 
 unsigned short BIT8 ; 
 int /*<<< orphan*/  DmaCmd_InitRxChannel ; 
 int /*<<< orphan*/  DmaCmd_InitTxChannel ; 
 int /*<<< orphan*/  NRARL ; 
 int /*<<< orphan*/  NRARU ; 
 int /*<<< orphan*/  NTARL ; 
 int /*<<< orphan*/  NTARU ; 
 int /*<<< orphan*/  RDMR ; 
 int /*<<< orphan*/  RMR ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int /*<<< orphan*/  RTCmd_PurgeTxFifo ; 
 int /*<<< orphan*/  TCLR ; 
 int /*<<< orphan*/  TCSR ; 
 int /*<<< orphan*/  TCmd_SelectTicrTxFifostatus ; 
 int /*<<< orphan*/  TCmd_SendFrame ; 
 unsigned int TESTFRAMESIZE ; 
 int /*<<< orphan*/  TICR ; 
 int /*<<< orphan*/  TMR ; 
 int /*<<< orphan*/  default_params ; 
 unsigned long jiffies ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 unsigned short usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_loopback (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_reset (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_sdlc_mode (struct mgsl_struct*) ; 

__attribute__((used)) static bool mgsl_dma_test( struct mgsl_struct *info )
{
	unsigned short FifoLevel;
	unsigned long phys_addr;
	unsigned int FrameSize;
	unsigned int i;
	char *TmpPtr;
	bool rc = true;
	unsigned short status=0;
	unsigned long EndTime;
	unsigned long flags;
	MGSL_PARAMS tmp_params;

	/* save current port options */
	memcpy(&tmp_params,&info->params,sizeof(MGSL_PARAMS));
	/* load default port options */
	memcpy(&info->params,&default_params,sizeof(MGSL_PARAMS));
	
#define TESTFRAMESIZE 40

	spin_lock_irqsave(&info->irq_spinlock,flags);
	
	/* setup 16C32 for SDLC DMA transfer mode */

	usc_reset(info);
	usc_set_sdlc_mode(info);
	usc_enable_loopback(info,1);
	
	/* Reprogram the RDMR so that the 16C32 does NOT clear the count
	 * field of the buffer entry after fetching buffer address. This
	 * way we can detect a DMA failure for a DMA read (which should be
	 * non-destructive to system memory) before we try and write to
	 * memory (where a failure could corrupt system memory).
	 */

	/* Receive DMA mode Register (RDMR)
	 * 
	 * <15..14>	11	DMA mode = Linked List Buffer mode
	 * <13>		1	RSBinA/L = store Rx status Block in List entry
	 * <12>		0	1 = Clear count of List Entry after fetching
	 * <11..10>	00	Address mode = Increment
	 * <9>		1	Terminate Buffer on RxBound
	 * <8>		0	Bus Width = 16bits
	 * <7..0>		?	status Bits (write as 0s)
	 * 
	 * 1110 0010 0000 0000 = 0xe200
	 */

	usc_OutDmaReg( info, RDMR, 0xe200 );
	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);


	/* SETUP TRANSMIT AND RECEIVE DMA BUFFERS */

	FrameSize = TESTFRAMESIZE;

	/* setup 1st transmit buffer entry: */
	/* with frame size and transmit control word */

	info->tx_buffer_list[0].count  = FrameSize;
	info->tx_buffer_list[0].rcc    = FrameSize;
	info->tx_buffer_list[0].status = 0x4000;

	/* build a transmit frame in 1st transmit DMA buffer */

	TmpPtr = info->tx_buffer_list[0].virt_addr;
	for (i = 0; i < FrameSize; i++ )
		*TmpPtr++ = i;

	/* setup 1st receive buffer entry: */
	/* clear status, set max receive buffer size */

	info->rx_buffer_list[0].status = 0;
	info->rx_buffer_list[0].count = FrameSize + 4;

	/* zero out the 1st receive buffer */

	memset( info->rx_buffer_list[0].virt_addr, 0, FrameSize + 4 );

	/* Set count field of next buffer entries to prevent */
	/* 16C32 from using buffers after the 1st one. */

	info->tx_buffer_list[1].count = 0;
	info->rx_buffer_list[1].count = 0;
	

	/***************************/
	/* Program 16C32 receiver. */
	/***************************/
	
	spin_lock_irqsave(&info->irq_spinlock,flags);

	/* setup DMA transfers */
	usc_RTCmd( info, RTCmd_PurgeRxFifo );

	/* program 16C32 receiver with physical address of 1st DMA buffer entry */
	phys_addr = info->rx_buffer_list[0].phys_entry;
	usc_OutDmaReg( info, NRARL, (unsigned short)phys_addr );
	usc_OutDmaReg( info, NRARU, (unsigned short)(phys_addr >> 16) );

	/* Clear the Rx DMA status bits (read RDMR) and start channel */
	usc_InDmaReg( info, RDMR );
	usc_DmaCmd( info, DmaCmd_InitRxChannel );

	/* Enable Receiver (RMR <1..0> = 10) */
	usc_OutReg( info, RMR, (unsigned short)((usc_InReg(info, RMR) & 0xfffc) | 0x0002) );
	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);


	/*************************************************************/
	/* WAIT FOR RECEIVER TO DMA ALL PARAMETERS FROM BUFFER ENTRY */
	/*************************************************************/

	/* Wait 100ms for interrupt. */
	EndTime = jiffies + msecs_to_jiffies(100);

	for(;;) {
		if (time_after(jiffies, EndTime)) {
			rc = false;
			break;
		}

		spin_lock_irqsave(&info->irq_spinlock,flags);
		status = usc_InDmaReg( info, RDMR );
		spin_unlock_irqrestore(&info->irq_spinlock,flags);

		if ( !(status & BIT4) && (status & BIT5) ) {
			/* INITG (BIT 4) is inactive (no entry read in progress) AND */
			/* BUSY  (BIT 5) is active (channel still active). */
			/* This means the buffer entry read has completed. */
			break;
		}
	}


	/******************************/
	/* Program 16C32 transmitter. */
	/******************************/
	
	spin_lock_irqsave(&info->irq_spinlock,flags);

	/* Program the Transmit Character Length Register (TCLR) */
	/* and clear FIFO (TCC is loaded with TCLR on FIFO clear) */

	usc_OutReg( info, TCLR, (unsigned short)info->tx_buffer_list[0].count );
	usc_RTCmd( info, RTCmd_PurgeTxFifo );

	/* Program the address of the 1st DMA Buffer Entry in linked list */

	phys_addr = info->tx_buffer_list[0].phys_entry;
	usc_OutDmaReg( info, NTARL, (unsigned short)phys_addr );
	usc_OutDmaReg( info, NTARU, (unsigned short)(phys_addr >> 16) );

	/* unlatch Tx status bits, and start transmit channel. */

	usc_OutReg( info, TCSR, (unsigned short)(( usc_InReg(info, TCSR) & 0x0f00) | 0xfa) );
	usc_DmaCmd( info, DmaCmd_InitTxChannel );

	/* wait for DMA controller to fill transmit FIFO */

	usc_TCmd( info, TCmd_SelectTicrTxFifostatus );
	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);


	/**********************************/
	/* WAIT FOR TRANSMIT FIFO TO FILL */
	/**********************************/
	
	/* Wait 100ms */
	EndTime = jiffies + msecs_to_jiffies(100);

	for(;;) {
		if (time_after(jiffies, EndTime)) {
			rc = false;
			break;
		}

		spin_lock_irqsave(&info->irq_spinlock,flags);
		FifoLevel = usc_InReg(info, TICR) >> 8;
		spin_unlock_irqrestore(&info->irq_spinlock,flags);
			
		if ( FifoLevel < 16 )
			break;
		else
			if ( FrameSize < 32 ) {
				/* This frame is smaller than the entire transmit FIFO */
				/* so wait for the entire frame to be loaded. */
				if ( FifoLevel <= (32 - FrameSize) )
					break;
			}
	}


	if ( rc )
	{
		/* Enable 16C32 transmitter. */

		spin_lock_irqsave(&info->irq_spinlock,flags);
		
		/* Transmit mode Register (TMR), <1..0> = 10, Enable Transmitter */
		usc_TCmd( info, TCmd_SendFrame );
		usc_OutReg( info, TMR, (unsigned short)((usc_InReg(info, TMR) & 0xfffc) | 0x0002) );
		
		spin_unlock_irqrestore(&info->irq_spinlock,flags);

						
		/******************************/
		/* WAIT FOR TRANSMIT COMPLETE */
		/******************************/

		/* Wait 100ms */
		EndTime = jiffies + msecs_to_jiffies(100);

		/* While timer not expired wait for transmit complete */

		spin_lock_irqsave(&info->irq_spinlock,flags);
		status = usc_InReg( info, TCSR );
		spin_unlock_irqrestore(&info->irq_spinlock,flags);

		while ( !(status & (BIT6+BIT5+BIT4+BIT2+BIT1)) ) {
			if (time_after(jiffies, EndTime)) {
				rc = false;
				break;
			}

			spin_lock_irqsave(&info->irq_spinlock,flags);
			status = usc_InReg( info, TCSR );
			spin_unlock_irqrestore(&info->irq_spinlock,flags);
		}
	}


	if ( rc ){
		/* CHECK FOR TRANSMIT ERRORS */
		if ( status & (BIT5 + BIT1) ) 
			rc = false;
	}

	if ( rc ) {
		/* WAIT FOR RECEIVE COMPLETE */

		/* Wait 100ms */
		EndTime = jiffies + msecs_to_jiffies(100);

		/* Wait for 16C32 to write receive status to buffer entry. */
		status=info->rx_buffer_list[0].status;
		while ( status == 0 ) {
			if (time_after(jiffies, EndTime)) {
				rc = false;
				break;
			}
			status=info->rx_buffer_list[0].status;
		}
	}


	if ( rc ) {
		/* CHECK FOR RECEIVE ERRORS */
		status = info->rx_buffer_list[0].status;

		if ( status & (BIT8 + BIT3 + BIT1) ) {
			/* receive error has occurred */
			rc = false;
		} else {
			if ( memcmp( info->tx_buffer_list[0].virt_addr ,
				info->rx_buffer_list[0].virt_addr, FrameSize ) ){
				rc = false;
			}
		}
	}

	spin_lock_irqsave(&info->irq_spinlock,flags);
	usc_reset( info );
	spin_unlock_irqrestore(&info->irq_spinlock,flags);

	/* restore current port options */
	memcpy(&info->params,&tmp_params,sizeof(MGSL_PARAMS));
	
	return rc;

}