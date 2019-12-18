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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int flags; } ;
struct mgsl_struct {int current_rx_buffer; int rx_buffer_count; TYPE_1__ params; TYPE_2__* rx_buffer_list; } ;
struct TYPE_4__ {int phys_entry; int /*<<< orphan*/  count; scalar_t__ status; } ;
typedef  TYPE_2__ DMABUFFERENTRY ;

/* Variables and functions */
 int BIT1 ; 
 int BIT13 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 int /*<<< orphan*/  CCSR ; 
 int /*<<< orphan*/  DICR ; 
 int /*<<< orphan*/  DISABLE_UNCONDITIONAL ; 
 unsigned long DMABUFFERSIZE ; 
 int /*<<< orphan*/  DmaCmd_InitRxChannel ; 
 int /*<<< orphan*/  DmaCmd_PauseRxChannel ; 
 int /*<<< orphan*/  ENABLE_AUTO_DCD ; 
 int /*<<< orphan*/  ENABLE_UNCONDITIONAL ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int /*<<< orphan*/  NRARL ; 
 int /*<<< orphan*/  NRARU ; 
 int /*<<< orphan*/  RCmd_EnterHuntmode ; 
 int /*<<< orphan*/  RDIAR ; 
 int RECEIVE_DATA ; 
 int RECEIVE_STATUS ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int RXSTATUS_ALL ; 
 int /*<<< orphan*/  mgsl_reset_rx_dma_buffers (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableInterrupts (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_EnableReceiver (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usc_RCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int) ; 

__attribute__((used)) static void usc_process_rxoverrun_sync( struct mgsl_struct *info )
{
	int start_index;
	int end_index;
	int frame_start_index;
	bool start_of_frame_found = false;
	bool end_of_frame_found = false;
	bool reprogram_dma = false;

	DMABUFFERENTRY *buffer_list = info->rx_buffer_list;
	u32 phys_addr;

	usc_DmaCmd( info, DmaCmd_PauseRxChannel );
	usc_RCmd( info, RCmd_EnterHuntmode );
	usc_RTCmd( info, RTCmd_PurgeRxFifo );

	/* CurrentRxBuffer points to the 1st buffer of the next */
	/* possibly available receive frame. */
	
	frame_start_index = start_index = end_index = info->current_rx_buffer;

	/* Search for an unfinished string of buffers. This means */
	/* that a receive frame started (at least one buffer with */
	/* count set to zero) but there is no terminiting buffer */
	/* (status set to non-zero). */

	while( !buffer_list[end_index].count )
	{
		/* Count field has been reset to zero by 16C32. */
		/* This buffer is currently in use. */

		if ( !start_of_frame_found )
		{
			start_of_frame_found = true;
			frame_start_index = end_index;
			end_of_frame_found = false;
		}

		if ( buffer_list[end_index].status )
		{
			/* Status field has been set by 16C32. */
			/* This is the last buffer of a received frame. */

			/* We want to leave the buffers for this frame intact. */
			/* Move on to next possible frame. */

			start_of_frame_found = false;
			end_of_frame_found = true;
		}

  		/* advance to next buffer entry in linked list */
  		end_index++;
  		if ( end_index == info->rx_buffer_count )
  			end_index = 0;

		if ( start_index == end_index )
		{
			/* The entire list has been searched with all Counts == 0 and */
			/* all Status == 0. The receive buffers are */
			/* completely screwed, reset all receive buffers! */
			mgsl_reset_rx_dma_buffers( info );
			frame_start_index = 0;
			start_of_frame_found = false;
			reprogram_dma = true;
			break;
		}
	}

	if ( start_of_frame_found && !end_of_frame_found )
	{
		/* There is an unfinished string of receive DMA buffers */
		/* as a result of the receiver overrun. */

		/* Reset the buffers for the unfinished frame */
		/* and reprogram the receive DMA controller to start */
		/* at the 1st buffer of unfinished frame. */

		start_index = frame_start_index;

		do
		{
			*((unsigned long *)&(info->rx_buffer_list[start_index++].count)) = DMABUFFERSIZE;

  			/* Adjust index for wrap around. */
  			if ( start_index == info->rx_buffer_count )
  				start_index = 0;

		} while( start_index != end_index );

		reprogram_dma = true;
	}

	if ( reprogram_dma )
	{
		usc_UnlatchRxstatusBits(info,RXSTATUS_ALL);
		usc_ClearIrqPendingBits(info, RECEIVE_DATA|RECEIVE_STATUS);
		usc_UnlatchRxstatusBits(info, RECEIVE_DATA|RECEIVE_STATUS);
		
		usc_EnableReceiver(info,DISABLE_UNCONDITIONAL);
		
		/* This empties the receive FIFO and loads the RCC with RCLR */
		usc_OutReg( info, CCSR, (u16)(usc_InReg(info,CCSR) | BIT13) );

		/* program 16C32 with physical address of 1st DMA buffer entry */
		phys_addr = info->rx_buffer_list[frame_start_index].phys_entry;
		usc_OutDmaReg( info, NRARL, (u16)phys_addr );
		usc_OutDmaReg( info, NRARU, (u16)(phys_addr >> 16) );

		usc_UnlatchRxstatusBits( info, RXSTATUS_ALL );
		usc_ClearIrqPendingBits( info, RECEIVE_DATA + RECEIVE_STATUS );
		usc_EnableInterrupts( info, RECEIVE_STATUS );

		/* 1. Arm End of Buffer (EOB) Receive DMA Interrupt (BIT2 of RDIAR) */
		/* 2. Enable Receive DMA Interrupts (BIT1 of DICR) */

		usc_OutDmaReg( info, RDIAR, BIT3 + BIT2 );
		usc_OutDmaReg( info, DICR, (u16)(usc_InDmaReg(info,DICR) | BIT1) );
		usc_DmaCmd( info, DmaCmd_InitRxChannel );
		if ( info->params.flags & HDLC_FLAG_AUTO_DCD )
			usc_EnableReceiver(info,ENABLE_AUTO_DCD);
		else
			usc_EnableReceiver(info,ENABLE_UNCONDITIONAL);
	}
	else
	{
		/* This empties the receive FIFO and loads the RCC with RCLR */
		usc_OutReg( info, CCSR, (u16)(usc_InReg(info,CCSR) | BIT13) );
		usc_RTCmd( info, RTCmd_PurgeRxFifo );
	}

}