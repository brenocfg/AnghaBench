#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u16 ;
struct brcms_hardware {size_t* xmtfifo_sz; struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FIFOSIZE0 ; 
 int /*<<< orphan*/  M_FIFOSIZE1 ; 
 int /*<<< orphan*/  M_FIFOSIZE2 ; 
 int /*<<< orphan*/  M_FIFOSIZE3 ; 
 size_t NFIFO ; 
 size_t TXFIFOCMD_FIFOSEL_SHIFT ; 
 size_t TXFIFOCMD_RESET_MASK ; 
 size_t TXFIFO_FIFOTOP_SHIFT ; 
 size_t TXFIFO_START_BLK ; 
 size_t TX_AC_BE_FIFO ; 
 size_t TX_AC_BK_FIFO ; 
 size_t TX_AC_VI_FIFO ; 
 size_t TX_AC_VO_FIFO ; 
 size_t TX_ATIM_FIFO ; 
 size_t TX_BCMC_FIFO ; 
 int /*<<< orphan*/  bcma_write16 (struct bcma_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmtfifocmd ; 
 int /*<<< orphan*/  xmtfifodef ; 
 int /*<<< orphan*/  xmtfifodef1 ; 

__attribute__((used)) static void brcms_b_corerev_fifofixup(struct brcms_hardware *wlc_hw)
{
	struct bcma_device *core = wlc_hw->d11core;
	u16 fifo_nu;
	u16 txfifo_startblk = TXFIFO_START_BLK, txfifo_endblk;
	u16 txfifo_def, txfifo_def1;
	u16 txfifo_cmd;

	/* tx fifos start at TXFIFO_START_BLK from the Base address */
	txfifo_startblk = TXFIFO_START_BLK;

	/* sequence of operations:  reset fifo, set fifo size, reset fifo */
	for (fifo_nu = 0; fifo_nu < NFIFO; fifo_nu++) {

		txfifo_endblk = txfifo_startblk + wlc_hw->xmtfifo_sz[fifo_nu];
		txfifo_def = (txfifo_startblk & 0xff) |
		    (((txfifo_endblk - 1) & 0xff) << TXFIFO_FIFOTOP_SHIFT);
		txfifo_def1 = ((txfifo_startblk >> 8) & 0x1) |
		    ((((txfifo_endblk -
			1) >> 8) & 0x1) << TXFIFO_FIFOTOP_SHIFT);
		txfifo_cmd =
		    TXFIFOCMD_RESET_MASK | (fifo_nu << TXFIFOCMD_FIFOSEL_SHIFT);

		bcma_write16(core, D11REGOFFS(xmtfifocmd), txfifo_cmd);
		bcma_write16(core, D11REGOFFS(xmtfifodef), txfifo_def);
		bcma_write16(core, D11REGOFFS(xmtfifodef1), txfifo_def1);

		bcma_write16(core, D11REGOFFS(xmtfifocmd), txfifo_cmd);

		txfifo_startblk += wlc_hw->xmtfifo_sz[fifo_nu];
	}
	/*
	 * need to propagate to shm location to be in sync since ucode/hw won't
	 * do this
	 */
	brcms_b_write_shm(wlc_hw, M_FIFOSIZE0,
			   wlc_hw->xmtfifo_sz[TX_AC_BE_FIFO]);
	brcms_b_write_shm(wlc_hw, M_FIFOSIZE1,
			   wlc_hw->xmtfifo_sz[TX_AC_VI_FIFO]);
	brcms_b_write_shm(wlc_hw, M_FIFOSIZE2,
			   ((wlc_hw->xmtfifo_sz[TX_AC_VO_FIFO] << 8) | wlc_hw->
			    xmtfifo_sz[TX_AC_BK_FIFO]));
	brcms_b_write_shm(wlc_hw, M_FIFOSIZE3,
			   ((wlc_hw->xmtfifo_sz[TX_ATIM_FIFO] << 8) | wlc_hw->
			    xmtfifo_sz[TX_BCMC_FIFO]));
}