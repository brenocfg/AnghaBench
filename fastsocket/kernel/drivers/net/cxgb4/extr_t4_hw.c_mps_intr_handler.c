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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  BUBBLE 140 
 int CLSINT ; 
#define  FILTMEM 139 
#define  FRMERR 138 
#define  HASHSRAM 137 
#define  MATCHSRAM 136 
#define  MATCHTCAM 135 
#define  MISCPERR 134 
 int /*<<< orphan*/  MPS_CLS_INT_CAUSE ; 
 int /*<<< orphan*/  MPS_INT_CAUSE ; 
 int /*<<< orphan*/  MPS_RX_PERR_INT_CAUSE ; 
 int /*<<< orphan*/  MPS_STAT_PERR_INT_CAUSE_RX_FIFO ; 
 int /*<<< orphan*/  MPS_STAT_PERR_INT_CAUSE_SRAM ; 
 int /*<<< orphan*/  MPS_STAT_PERR_INT_CAUSE_TX_FIFO ; 
 int /*<<< orphan*/  MPS_TRC_INT_CAUSE ; 
 int /*<<< orphan*/  MPS_TX_INT_CAUSE ; 
#define  NCSIFIFO 133 
#define  PKTFIFO 132 
 int RXINT ; 
#define  SECNTERR 131 
 int STATINT ; 
#define  TPFIFO 130 
 int TRCINT ; 
#define  TXDATAFIFO 129 
#define  TXDESCFIFO 128 
 int TXINT ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 int t4_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,struct intr_info const*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mps_intr_handler(struct adapter *adapter)
{
	static const struct intr_info mps_rx_intr_info[] = {
		{ 0xffffff, "MPS Rx parity error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_tx_intr_info[] = {
		{ TPFIFO, "MPS Tx TP FIFO parity error", -1, 1 },
		{ NCSIFIFO, "MPS Tx NC-SI FIFO parity error", -1, 1 },
		{ TXDATAFIFO, "MPS Tx data FIFO parity error", -1, 1 },
		{ TXDESCFIFO, "MPS Tx desc FIFO parity error", -1, 1 },
		{ BUBBLE, "MPS Tx underflow", -1, 1 },
		{ SECNTERR, "MPS Tx SOP/EOP error", -1, 1 },
		{ FRMERR, "MPS Tx framing error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_trc_intr_info[] = {
		{ FILTMEM, "MPS TRC filter parity error", -1, 1 },
		{ PKTFIFO, "MPS TRC packet FIFO parity error", -1, 1 },
		{ MISCPERR, "MPS TRC misc parity error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_stat_sram_intr_info[] = {
		{ 0x1fffff, "MPS statistics SRAM parity error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_stat_tx_intr_info[] = {
		{ 0xfffff, "MPS statistics Tx FIFO parity error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_stat_rx_intr_info[] = {
		{ 0xffffff, "MPS statistics Rx FIFO parity error", -1, 1 },
		{ 0 }
	};
	static const struct intr_info mps_cls_intr_info[] = {
		{ MATCHSRAM, "MPS match SRAM parity error", -1, 1 },
		{ MATCHTCAM, "MPS match TCAM parity error", -1, 1 },
		{ HASHSRAM, "MPS hash SRAM parity error", -1, 1 },
		{ 0 }
	};

	int fat;

	fat = t4_handle_intr_status(adapter, MPS_RX_PERR_INT_CAUSE,
				    mps_rx_intr_info) +
	      t4_handle_intr_status(adapter, MPS_TX_INT_CAUSE,
				    mps_tx_intr_info) +
	      t4_handle_intr_status(adapter, MPS_TRC_INT_CAUSE,
				    mps_trc_intr_info) +
	      t4_handle_intr_status(adapter, MPS_STAT_PERR_INT_CAUSE_SRAM,
				    mps_stat_sram_intr_info) +
	      t4_handle_intr_status(adapter, MPS_STAT_PERR_INT_CAUSE_TX_FIFO,
				    mps_stat_tx_intr_info) +
	      t4_handle_intr_status(adapter, MPS_STAT_PERR_INT_CAUSE_RX_FIFO,
				    mps_stat_rx_intr_info) +
	      t4_handle_intr_status(adapter, MPS_CLS_INT_CAUSE,
				    mps_cls_intr_info);

	t4_write_reg(adapter, MPS_INT_CAUSE, CLSINT | TRCINT |
		     RXINT | TXINT | STATINT);
	t4_read_reg(adapter, MPS_INT_CAUSE);                    /* flush */
	if (fat)
		t4_fatal_err(adapter);
}