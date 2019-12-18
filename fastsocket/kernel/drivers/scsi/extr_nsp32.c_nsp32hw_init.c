#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int BaseAddress; int trans_method; int clock; } ;
typedef  TYPE_1__ nsp32_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_WIDTH ; 
 unsigned long AUTOSEL_TIMING_SEL ; 
 unsigned long BMREQ_NEGATE_TIMING_SEL ; 
 unsigned long BMSTOP_CHANGE2_NONDATA_PHASE ; 
 int /*<<< orphan*/  BM_CNT ; 
 int /*<<< orphan*/  BM_CYCLE ; 
 int BPWR ; 
 int /*<<< orphan*/  CFG_LATE_CACHE ; 
 int /*<<< orphan*/  CLOCK_DIV ; 
 unsigned long DELAYED_BMSTART ; 
 int /*<<< orphan*/  EXT_PORT ; 
 int /*<<< orphan*/  EXT_PORT_DDR ; 
 int /*<<< orphan*/  FIFO_EMPTY_SHLD_COUNT ; 
 int /*<<< orphan*/  FIFO_FULL_SHLD_COUNT ; 
 unsigned long IRQSELECT_AUTO_SCSI_SEQ_IRQ ; 
 unsigned long IRQSELECT_FIFO_SHLD_IRQ ; 
 unsigned long IRQSELECT_MASTER_ABORT_IRQ ; 
 unsigned long IRQSELECT_PHASE_CHANGE_IRQ ; 
 unsigned long IRQSELECT_RESELECT_IRQ ; 
 unsigned long IRQSELECT_SCSIRESET_IRQ ; 
 unsigned long IRQSELECT_TARGET_ABORT_IRQ ; 
 unsigned long IRQSELECT_TIMER_IRQ ; 
 unsigned short IRQSTATUS_ANY_IRQ ; 
 int /*<<< orphan*/  IRQ_CONTROL ; 
 int /*<<< orphan*/  IRQ_CONTROL_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_SELECT ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LED_OFF ; 
 unsigned long MASTER_TERMINATION_SELECT ; 
 int MEMRD_CMD1 ; 
 int /*<<< orphan*/  MISC_WR ; 
 int /*<<< orphan*/  NSP32_DEBUG_INIT ; 
 int NSP32_TRANSFER_BUSMASTER ; 
 int NSP32_TRANSFER_MMIO ; 
 int NSP32_TRANSFER_PIO ; 
 int /*<<< orphan*/  PARITY_CONTROL ; 
 unsigned long SCSI_DIRECTION_DETECTOR_SELECT ; 
 int /*<<< orphan*/  SCSI_EXECUTE_PHASE ; 
 int /*<<< orphan*/  SEL_TIMEOUT_TIME ; 
 int /*<<< orphan*/  SEL_TIME_OUT ; 
 unsigned char SENSE ; 
 int SGT_AUTO_PARA_MEMED_CMD ; 
 int /*<<< orphan*/  SYNC_REG ; 
 int /*<<< orphan*/  TERM_PWR_CONTROL ; 
 int /*<<< orphan*/  TIMER_SET ; 
 int /*<<< orphan*/  TIMER_STOP ; 
 int /*<<< orphan*/  TRANSFER_CONTROL ; 
 int TRUE ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char nsp32_index_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long nsp32_index_read4 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_index_write1 (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp32_index_write2 (unsigned int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 unsigned short nsp32_read2 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write4 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsp32hw_init(nsp32_hw_data *data)
{
	unsigned int   base = data->BaseAddress;
	unsigned short irq_stat;
	unsigned long  lc_reg;
	unsigned char  power;

	lc_reg = nsp32_index_read4(base, CFG_LATE_CACHE);
	if ((lc_reg & 0xff00) == 0) {
		lc_reg |= (0x20 << 8);
		nsp32_index_write2(base, CFG_LATE_CACHE, lc_reg & 0xffff);
	}

	nsp32_write2(base, IRQ_CONTROL,        IRQ_CONTROL_ALL_IRQ_MASK);
	nsp32_write2(base, TRANSFER_CONTROL,   0);
	nsp32_write4(base, BM_CNT,             0);
	nsp32_write2(base, SCSI_EXECUTE_PHASE, 0);

	do {
		irq_stat = nsp32_read2(base, IRQ_STATUS);
		nsp32_dbg(NSP32_DEBUG_INIT, "irq_stat 0x%x", irq_stat);
	} while (irq_stat & IRQSTATUS_ANY_IRQ);

	/*
	 * Fill FIFO_FULL_SHLD, FIFO_EMPTY_SHLD. Below parameter is
	 *  designated by specification.
	 */
	if ((data->trans_method & NSP32_TRANSFER_PIO) ||
	    (data->trans_method & NSP32_TRANSFER_MMIO)) {
		nsp32_index_write1(base, FIFO_FULL_SHLD_COUNT,  0x40);
		nsp32_index_write1(base, FIFO_EMPTY_SHLD_COUNT, 0x40);
	} else if (data->trans_method & NSP32_TRANSFER_BUSMASTER) {
		nsp32_index_write1(base, FIFO_FULL_SHLD_COUNT,  0x10);
		nsp32_index_write1(base, FIFO_EMPTY_SHLD_COUNT, 0x60);
	} else {
		nsp32_dbg(NSP32_DEBUG_INIT, "unknown transfer mode");
	}

	nsp32_dbg(NSP32_DEBUG_INIT, "full 0x%x emp 0x%x",
		  nsp32_index_read1(base, FIFO_FULL_SHLD_COUNT),
		  nsp32_index_read1(base, FIFO_EMPTY_SHLD_COUNT));

	nsp32_index_write1(base, CLOCK_DIV, data->clock);
	nsp32_index_write1(base, BM_CYCLE,  MEMRD_CMD1 | SGT_AUTO_PARA_MEMED_CMD);
	nsp32_write1(base, PARITY_CONTROL, 0);	/* parity check is disable */

	/*
	 * initialize MISC_WRRD register
	 * 
	 * Note: Designated parameters is obeyed as following:
	 *	MISC_SCSI_DIRECTION_DETECTOR_SELECT: It must be set.
	 *	MISC_MASTER_TERMINATION_SELECT:      It must be set.
	 *	MISC_BMREQ_NEGATE_TIMING_SEL:	     It should be set.
	 *	MISC_AUTOSEL_TIMING_SEL:	     It should be set.
	 *	MISC_BMSTOP_CHANGE2_NONDATA_PHASE:   It should be set.
	 *	MISC_DELAYED_BMSTART:		     It's selected for safety.
	 *
	 * Note: If MISC_BMSTOP_CHANGE2_NONDATA_PHASE is set, then
	 *	we have to set TRANSFERCONTROL_BM_START as 0 and set
	 *	appropriate value before restarting bus master transfer.
	 */
	nsp32_index_write2(base, MISC_WR,
			   (SCSI_DIRECTION_DETECTOR_SELECT |
			    DELAYED_BMSTART                |
			    MASTER_TERMINATION_SELECT      |
			    BMREQ_NEGATE_TIMING_SEL        |
			    AUTOSEL_TIMING_SEL             |
			    BMSTOP_CHANGE2_NONDATA_PHASE));

	nsp32_index_write1(base, TERM_PWR_CONTROL, 0);
	power = nsp32_index_read1(base, TERM_PWR_CONTROL);
	if (!(power & SENSE)) {
		nsp32_msg(KERN_INFO, "term power on");
		nsp32_index_write1(base, TERM_PWR_CONTROL, BPWR);
	}

	nsp32_write2(base, TIMER_SET, TIMER_STOP);
	nsp32_write2(base, TIMER_SET, TIMER_STOP); /* Required 2 times */

	nsp32_write1(base, SYNC_REG,     0);
	nsp32_write1(base, ACK_WIDTH,    0);
	nsp32_write2(base, SEL_TIME_OUT, SEL_TIMEOUT_TIME);

	/*
	 * enable to select designated IRQ (except for
	 * IRQSELECT_SERR, IRQSELECT_PERR, IRQSELECT_BMCNTERR)
	 */
	nsp32_index_write2(base, IRQ_SELECT, IRQSELECT_TIMER_IRQ         |
			                     IRQSELECT_SCSIRESET_IRQ     |
			                     IRQSELECT_FIFO_SHLD_IRQ     |
			                     IRQSELECT_RESELECT_IRQ      |
			                     IRQSELECT_PHASE_CHANGE_IRQ  |
			                     IRQSELECT_AUTO_SCSI_SEQ_IRQ |
			                  //   IRQSELECT_BMCNTERR_IRQ      |
			                     IRQSELECT_TARGET_ABORT_IRQ  |
			                     IRQSELECT_MASTER_ABORT_IRQ );
	nsp32_write2(base, IRQ_CONTROL, 0);

	/* PCI LED off */
	nsp32_index_write1(base, EXT_PORT_DDR, LED_OFF);
	nsp32_index_write1(base, EXT_PORT,     LED_OFF);

	return TRUE;
}