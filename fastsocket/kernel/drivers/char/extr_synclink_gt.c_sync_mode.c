#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; int encoding; int crc_type; int preamble; int preamble_length; int flags; int clock_speed; scalar_t__ loopback; } ;
struct slgt_info {int if_mode; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned short BIT0 ; 
 unsigned short BIT1 ; 
 unsigned short BIT10 ; 
 unsigned short BIT11 ; 
 unsigned short BIT12 ; 
 unsigned short BIT13 ; 
 unsigned short BIT14 ; 
 unsigned short BIT15 ; 
 unsigned short BIT2 ; 
 unsigned short BIT3 ; 
 unsigned short BIT4 ; 
 unsigned short BIT5 ; 
 unsigned short BIT6 ; 
 unsigned short BIT7 ; 
 unsigned short BIT8 ; 
 unsigned short BIT9 ; 
 int /*<<< orphan*/  CCR ; 
#define  HDLC_CRC_16_CCITT 147 
#define  HDLC_CRC_32_CCITT 146 
 int HDLC_CRC_MASK ; 
#define  HDLC_ENCODING_BIPHASE_LEVEL 145 
#define  HDLC_ENCODING_BIPHASE_MARK 144 
#define  HDLC_ENCODING_BIPHASE_SPACE 143 
#define  HDLC_ENCODING_DIFF_BIPHASE_LEVEL 142 
#define  HDLC_ENCODING_NRZB 141 
#define  HDLC_ENCODING_NRZI 140 
#define  HDLC_ENCODING_NRZI_MARK 139 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int HDLC_FLAG_RXC_BRG ; 
 int HDLC_FLAG_RXC_DPLL ; 
 int HDLC_FLAG_RXC_TXCPIN ; 
 int HDLC_FLAG_TXC_BRG ; 
 int HDLC_FLAG_TXC_DPLL ; 
 int HDLC_FLAG_TXC_RXCPIN ; 
#define  HDLC_PREAMBLE_LENGTH_16BITS 138 
#define  HDLC_PREAMBLE_LENGTH_32BITS 137 
#define  HDLC_PREAMBLE_LENGTH_64BITS 136 
#define  HDLC_PREAMBLE_PATTERN_01 135 
#define  HDLC_PREAMBLE_PATTERN_10 134 
#define  HDLC_PREAMBLE_PATTERN_FLAGS 133 
 int HDLC_PREAMBLE_PATTERN_NONE ; 
#define  HDLC_PREAMBLE_PATTERN_ONES 132 
#define  HDLC_PREAMBLE_PATTERN_ZEROS 131 
 int IRQ_ALL ; 
 int IRQ_MASTER ; 
 int MGSL_INTERFACE_RTS_EN ; 
#define  MGSL_MODE_BISYNC 130 
#define  MGSL_MODE_MONOSYNC 129 
#define  MGSL_MODE_RAW 128 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  SCR ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TPR ; 
 int /*<<< orphan*/  enable_loopback (struct slgt_info*) ; 
 int /*<<< orphan*/  msc_set_vcr (struct slgt_info*) ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  set_rate (struct slgt_info*,int) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int) ; 
 int /*<<< orphan*/  tx_set_idle (struct slgt_info*) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg8 (struct slgt_info*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void sync_mode(struct slgt_info *info)
{
	unsigned short val;

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
	tx_stop(info);
	rx_stop(info);

	/* TCR (tx control)
	 *
	 * 15..13  mode, 000=HDLC 001=raw 010=async 011=monosync 100=bisync
	 * 12..10  encoding
	 * 09      CRC enable
	 * 08      CRC32
	 * 07      1=RTS driver control
	 * 06      preamble enable
	 * 05..04  preamble length
	 * 03      share open/close flag
	 * 02      reset
	 * 01      enable
	 * 00      auto-CTS enable
	 */
	val = BIT2;

	switch(info->params.mode) {
	case MGSL_MODE_MONOSYNC: val |= BIT14 + BIT13; break;
	case MGSL_MODE_BISYNC:   val |= BIT15; break;
	case MGSL_MODE_RAW:      val |= BIT13; break;
	}
	if (info->if_mode & MGSL_INTERFACE_RTS_EN)
		val |= BIT7;

	switch(info->params.encoding)
	{
	case HDLC_ENCODING_NRZB:          val |= BIT10; break;
	case HDLC_ENCODING_NRZI_MARK:     val |= BIT11; break;
	case HDLC_ENCODING_NRZI:          val |= BIT11 + BIT10; break;
	case HDLC_ENCODING_BIPHASE_MARK:  val |= BIT12; break;
	case HDLC_ENCODING_BIPHASE_SPACE: val |= BIT12 + BIT10; break;
	case HDLC_ENCODING_BIPHASE_LEVEL: val |= BIT12 + BIT11; break;
	case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: val |= BIT12 + BIT11 + BIT10; break;
	}

	switch (info->params.crc_type & HDLC_CRC_MASK)
	{
	case HDLC_CRC_16_CCITT: val |= BIT9; break;
	case HDLC_CRC_32_CCITT: val |= BIT9 + BIT8; break;
	}

	if (info->params.preamble != HDLC_PREAMBLE_PATTERN_NONE)
		val |= BIT6;

	switch (info->params.preamble_length)
	{
	case HDLC_PREAMBLE_LENGTH_16BITS: val |= BIT5; break;
	case HDLC_PREAMBLE_LENGTH_32BITS: val |= BIT4; break;
	case HDLC_PREAMBLE_LENGTH_64BITS: val |= BIT5 + BIT4; break;
	}

	if (info->params.flags & HDLC_FLAG_AUTO_CTS)
		val |= BIT0;

	wr_reg16(info, TCR, val);

	/* TPR (transmit preamble) */

	switch (info->params.preamble)
	{
	case HDLC_PREAMBLE_PATTERN_FLAGS: val = 0x7e; break;
	case HDLC_PREAMBLE_PATTERN_ONES:  val = 0xff; break;
	case HDLC_PREAMBLE_PATTERN_ZEROS: val = 0x00; break;
	case HDLC_PREAMBLE_PATTERN_10:    val = 0x55; break;
	case HDLC_PREAMBLE_PATTERN_01:    val = 0xaa; break;
	default:                          val = 0x7e; break;
	}
	wr_reg8(info, TPR, (unsigned char)val);

	/* RCR (rx control)
	 *
	 * 15..13  mode, 000=HDLC 001=raw 010=async 011=monosync 100=bisync
	 * 12..10  encoding
	 * 09      CRC enable
	 * 08      CRC32
	 * 07..03  reserved, must be 0
	 * 02      reset
	 * 01      enable
	 * 00      auto-DCD enable
	 */
	val = 0;

	switch(info->params.mode) {
	case MGSL_MODE_MONOSYNC: val |= BIT14 + BIT13; break;
	case MGSL_MODE_BISYNC:   val |= BIT15; break;
	case MGSL_MODE_RAW:      val |= BIT13; break;
	}

	switch(info->params.encoding)
	{
	case HDLC_ENCODING_NRZB:          val |= BIT10; break;
	case HDLC_ENCODING_NRZI_MARK:     val |= BIT11; break;
	case HDLC_ENCODING_NRZI:          val |= BIT11 + BIT10; break;
	case HDLC_ENCODING_BIPHASE_MARK:  val |= BIT12; break;
	case HDLC_ENCODING_BIPHASE_SPACE: val |= BIT12 + BIT10; break;
	case HDLC_ENCODING_BIPHASE_LEVEL: val |= BIT12 + BIT11; break;
	case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: val |= BIT12 + BIT11 + BIT10; break;
	}

	switch (info->params.crc_type & HDLC_CRC_MASK)
	{
	case HDLC_CRC_16_CCITT: val |= BIT9; break;
	case HDLC_CRC_32_CCITT: val |= BIT9 + BIT8; break;
	}

	if (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT0;

	wr_reg16(info, RCR, val);

	/* CCR (clock control)
	 *
	 * 07..05  tx clock source
	 * 04..02  rx clock source
	 * 01      auxclk enable
	 * 00      BRG enable
	 */
	val = 0;

	if (info->params.flags & HDLC_FLAG_TXC_BRG)
	{
		// when RxC source is DPLL, BRG generates 16X DPLL
		// reference clock, so take TxC from BRG/16 to get
		// transmit clock at actual data rate
		if (info->params.flags & HDLC_FLAG_RXC_DPLL)
			val |= BIT6 + BIT5;	/* 011, txclk = BRG/16 */
		else
			val |= BIT6;	/* 010, txclk = BRG */
	}
	else if (info->params.flags & HDLC_FLAG_TXC_DPLL)
		val |= BIT7;	/* 100, txclk = DPLL Input */
	else if (info->params.flags & HDLC_FLAG_TXC_RXCPIN)
		val |= BIT5;	/* 001, txclk = RXC Input */

	if (info->params.flags & HDLC_FLAG_RXC_BRG)
		val |= BIT3;	/* 010, rxclk = BRG */
	else if (info->params.flags & HDLC_FLAG_RXC_DPLL)
		val |= BIT4;	/* 100, rxclk = DPLL */
	else if (info->params.flags & HDLC_FLAG_RXC_TXCPIN)
		val |= BIT2;	/* 001, rxclk = TXC Input */

	if (info->params.clock_speed)
		val |= BIT1 + BIT0;

	wr_reg8(info, CCR, (unsigned char)val);

	if (info->params.flags & (HDLC_FLAG_TXC_DPLL + HDLC_FLAG_RXC_DPLL))
	{
		// program DPLL mode
		switch(info->params.encoding)
		{
		case HDLC_ENCODING_BIPHASE_MARK:
		case HDLC_ENCODING_BIPHASE_SPACE:
			val = BIT7; break;
		case HDLC_ENCODING_BIPHASE_LEVEL:
		case HDLC_ENCODING_DIFF_BIPHASE_LEVEL:
			val = BIT7 + BIT6; break;
		default: val = BIT6;	// NRZ encodings
		}
		wr_reg16(info, RCR, (unsigned short)(rd_reg16(info, RCR) | val));

		// DPLL requires a 16X reference clock from BRG
		set_rate(info, info->params.clock_speed * 16);
	}
	else
		set_rate(info, info->params.clock_speed);

	tx_set_idle(info);

	msc_set_vcr(info);

	/* SCR (serial control)
	 *
	 * 15  1=tx req on FIFO half empty
	 * 14  1=rx req on FIFO half full
	 * 13  tx data  IRQ enable
	 * 12  tx idle  IRQ enable
	 * 11  underrun IRQ enable
	 * 10  rx data  IRQ enable
	 * 09  rx idle  IRQ enable
	 * 08  overrun  IRQ enable
	 * 07  DSR      IRQ enable
	 * 06  CTS      IRQ enable
	 * 05  DCD      IRQ enable
	 * 04  RI       IRQ enable
	 * 03  reserved, must be zero
	 * 02  1=txd->rxd internal loopback enable
	 * 01  reserved, must be zero
	 * 00  1=master IRQ enable
	 */
	wr_reg16(info, SCR, BIT15 + BIT14 + BIT0);

	if (info->params.loopback)
		enable_loopback(info);
}