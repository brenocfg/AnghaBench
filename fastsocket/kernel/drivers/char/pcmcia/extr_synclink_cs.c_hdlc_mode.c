#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int flags; int encoding; scalar_t__ crc_type; int preamble; int preamble_length; int clock_speed; scalar_t__ loopback; } ;
struct TYPE_20__ {int serial_signals; scalar_t__ testing_irq; TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 unsigned char BIT7 ; 
 scalar_t__ CCR0 ; 
 scalar_t__ CCR1 ; 
 scalar_t__ CCR2 ; 
 scalar_t__ CCR3 ; 
 scalar_t__ CCR4 ; 
 scalar_t__ CHA ; 
 scalar_t__ CHB ; 
 scalar_t__ CMD_RXRESET ; 
 scalar_t__ CMD_TXRESET ; 
 scalar_t__ HDLC_CRC_32_CCITT ; 
 scalar_t__ HDLC_CRC_NONE ; 
#define  HDLC_ENCODING_BIPHASE_LEVEL 138 
#define  HDLC_ENCODING_BIPHASE_MARK 137 
#define  HDLC_ENCODING_BIPHASE_SPACE 136 
 int HDLC_ENCODING_NRZB ; 
#define  HDLC_ENCODING_NRZI 135 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_AUTO_DCD ; 
 int HDLC_FLAG_RXC_BRG ; 
 int HDLC_FLAG_RXC_DPLL ; 
 int HDLC_FLAG_TXC_BRG ; 
 int HDLC_FLAG_TXC_DPLL ; 
#define  HDLC_PREAMBLE_LENGTH_16BITS 134 
#define  HDLC_PREAMBLE_LENGTH_32BITS 133 
#define  HDLC_PREAMBLE_LENGTH_64BITS 132 
#define  HDLC_PREAMBLE_PATTERN_01 131 
#define  HDLC_PREAMBLE_PATTERN_10 130 
#define  HDLC_PREAMBLE_PATTERN_FLAGS 129 
 int HDLC_PREAMBLE_PATTERN_NONE ; 
#define  HDLC_PREAMBLE_PATTERN_ONES 128 
 scalar_t__ IRQ_ALLSENT ; 
 scalar_t__ IRQ_CTS ; 
 scalar_t__ IRQ_RXEOM ; 
 scalar_t__ IRQ_RXFIFO ; 
 scalar_t__ IRQ_TXFIFO ; 
 scalar_t__ IRQ_UNDERRUN ; 
 scalar_t__ ISR ; 
 scalar_t__ MODE ; 
 scalar_t__ PRE ; 
 scalar_t__ PVR ; 
 scalar_t__ RLCR ; 
 int SerialSignal_RTS ; 
 scalar_t__ XBCH ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_2__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  enable_auxclk (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_disable (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  irq_enable (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  issue_command (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  loopback_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  mgslpc_set_rate (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  port_irq_disable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  read_reg16 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  rx_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  set_reg_bits (TYPE_2__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  tx_set_idle (TYPE_2__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  wait_command_complete (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void hdlc_mode(MGSLPC_INFO *info)
{
	unsigned char val;
	unsigned char clkmode, clksubmode;

	/* disable all interrupts */
	irq_disable(info, CHA, 0xffff);
	irq_disable(info, CHB, 0xffff);
	port_irq_disable(info, 0xff);

	/* assume clock mode 0a, rcv=RxC xmt=TxC */
	clkmode = clksubmode = 0;
	if (info->params.flags & HDLC_FLAG_RXC_DPLL
	    && info->params.flags & HDLC_FLAG_TXC_DPLL) {
		/* clock mode 7a, rcv = DPLL, xmt = DPLL */
		clkmode = 7;
	} else if (info->params.flags & HDLC_FLAG_RXC_BRG
		 && info->params.flags & HDLC_FLAG_TXC_BRG) {
		/* clock mode 7b, rcv = BRG, xmt = BRG */
		clkmode = 7;
		clksubmode = 1;
	} else if (info->params.flags & HDLC_FLAG_RXC_DPLL) {
		if (info->params.flags & HDLC_FLAG_TXC_BRG) {
			/* clock mode 6b, rcv = DPLL, xmt = BRG/16 */
			clkmode = 6;
			clksubmode = 1;
		} else {
			/* clock mode 6a, rcv = DPLL, xmt = TxC */
			clkmode = 6;
		}
	} else if (info->params.flags & HDLC_FLAG_TXC_BRG) {
		/* clock mode 0b, rcv = RxC, xmt = BRG */
		clksubmode = 1;
	}

	/* MODE
	 *
	 * 07..06  MDS[1..0] 10 = transparent HDLC mode
	 * 05      ADM Address Mode, 0 = no addr recognition
	 * 04      TMD Timer Mode, 0 = external
	 * 03      RAC Receiver Active, 0 = inactive
	 * 02      RTS 0=RTS active during xmit, 1=RTS always active
	 * 01      TRS Timer Resolution, 1=512
	 * 00      TLP Test Loop, 0 = no loop
	 *
	 * 1000 0010
	 */
	val = 0x82;
	if (info->params.loopback)
		val |= BIT0;

	/* preserve RTS state */
	if (info->serial_signals & SerialSignal_RTS)
		val |= BIT2;
	write_reg(info, CHA + MODE, val);

	/* CCR0
	 *
	 * 07      PU Power Up, 1=active, 0=power down
	 * 06      MCE Master Clock Enable, 1=enabled
	 * 05      Reserved, 0
	 * 04..02  SC[2..0] Encoding
	 * 01..00  SM[1..0] Serial Mode, 00=HDLC
	 *
	 * 11000000
	 */
	val = 0xc0;
	switch (info->params.encoding)
	{
	case HDLC_ENCODING_NRZI:
		val |= BIT3;
		break;
	case HDLC_ENCODING_BIPHASE_SPACE:
		val |= BIT4;
		break;		// FM0
	case HDLC_ENCODING_BIPHASE_MARK:
		val |= BIT4 + BIT2;
		break;		// FM1
	case HDLC_ENCODING_BIPHASE_LEVEL:
		val |= BIT4 + BIT3;
		break;		// Manchester
	}
	write_reg(info, CHA + CCR0, val);

	/* CCR1
	 *
	 * 07      SFLG Shared Flag, 0 = disable shared flags
	 * 06      GALP Go Active On Loop, 0 = not used
	 * 05      GLP Go On Loop, 0 = not used
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      ITF Interframe Time Fill, 0=mark, 1=flag
	 * 02..00  CM[2..0] Clock Mode
	 *
	 * 0001 0000
	 */
	val = 0x10 + clkmode;
	write_reg(info, CHA + CCR1, val);

	/* CCR2
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate divisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 0=TxCLK is input
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      C32, CRC select, 0=CRC-16, 1=CRC-32
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0000 0000
	 */
	val = 0x00;
	if (clkmode == 2 || clkmode == 3 || clkmode == 6
	    || clkmode == 7 || (clkmode == 0 && clksubmode == 1))
		val |= BIT5;
	if (clksubmode)
		val |= BIT4;
	if (info->params.crc_type == HDLC_CRC_32_CCITT)
		val |= BIT1;
	if (info->params.encoding == HDLC_ENCODING_NRZB)
		val |= BIT0;
	write_reg(info, CHA + CCR2, val);

	/* CCR3
	 *
	 * 07..06  PRE[1..0] Preamble count 00=1, 01=2, 10=4, 11=8
	 * 05      EPT Enable preamble transmission, 1=enabled
	 * 04      RADD Receive address pushed to FIFO, 0=disabled
	 * 03      CRL CRC Reset Level, 0=FFFF
	 * 02      RCRC Rx CRC 0=On 1=Off
	 * 01      TCRC Tx CRC 0=On 1=Off
	 * 00      PSD DPLL Phase Shift Disable
	 *
	 * 0000 0000
	 */
	val = 0x00;
	if (info->params.crc_type == HDLC_CRC_NONE)
		val |= BIT2 + BIT1;
	if (info->params.preamble != HDLC_PREAMBLE_PATTERN_NONE)
		val |= BIT5;
	switch (info->params.preamble_length)
	{
	case HDLC_PREAMBLE_LENGTH_16BITS:
		val |= BIT6;
		break;
	case HDLC_PREAMBLE_LENGTH_32BITS:
		val |= BIT6;
		break;
	case HDLC_PREAMBLE_LENGTH_64BITS:
		val |= BIT7 + BIT6;
		break;
	}
	write_reg(info, CHA + CCR3, val);

	/* PRE - Preamble pattern */
	val = 0;
	switch (info->params.preamble)
	{
	case HDLC_PREAMBLE_PATTERN_FLAGS: val = 0x7e; break;
	case HDLC_PREAMBLE_PATTERN_10:    val = 0xaa; break;
	case HDLC_PREAMBLE_PATTERN_01:    val = 0x55; break;
	case HDLC_PREAMBLE_PATTERN_ONES:  val = 0xff; break;
	}
	write_reg(info, CHA + PRE, val);

	/* CCR4
	 *
	 * 07      MCK4 Master Clock Divide by 4, 1=enabled
	 * 06      EBRG Enhanced Baud Rate Generator Mode, 1=enabled
	 * 05      TST1 Test Pin, 0=normal operation
	 * 04      ICD Ivert Carrier Detect, 1=enabled (active low)
	 * 03..02  Reserved, must be 0
	 * 01..00  RFT[1..0] RxFIFO Threshold 00=32 bytes
	 *
	 * 0101 0000
	 */
	val = 0x50;
	write_reg(info, CHA + CCR4, val);
	if (info->params.flags & HDLC_FLAG_RXC_DPLL)
		mgslpc_set_rate(info, CHA, info->params.clock_speed * 16);
	else
		mgslpc_set_rate(info, CHA, info->params.clock_speed);

	/* RLCR Receive length check register
	 *
	 * 7     1=enable receive length check
	 * 6..0  Max frame length = (RL + 1) * 32
	 */
	write_reg(info, CHA + RLCR, 0);

	/* XBCH Transmit Byte Count High
	 *
	 * 07      DMA mode, 0 = interrupt driven
	 * 06      NRM, 0=ABM (ignored)
	 * 05      CAS Carrier Auto Start
	 * 04      XC Transmit Continuously (ignored)
	 * 03..00  XBC[10..8] Transmit byte count bits 10..8
	 *
	 * 0000 0000
	 */
	val = 0x00;
	if (info->params.flags & HDLC_FLAG_AUTO_DCD)
		val |= BIT5;
	write_reg(info, CHA + XBCH, val);
	enable_auxclk(info);
	if (info->params.loopback || info->testing_irq)
		loopback_enable(info);
	if (info->params.flags & HDLC_FLAG_AUTO_CTS)
	{
		irq_enable(info, CHB, IRQ_CTS);
		/* PVR[3] 1=AUTO CTS active */
		set_reg_bits(info, CHA + PVR, BIT3);
	} else
		clear_reg_bits(info, CHA + PVR, BIT3);

	irq_enable(info, CHA,
			 IRQ_RXEOM + IRQ_RXFIFO + IRQ_ALLSENT +
			 IRQ_UNDERRUN + IRQ_TXFIFO);
	issue_command(info, CHA, CMD_TXRESET + CMD_RXRESET);
	wait_command_complete(info, CHA);
	read_reg16(info, CHA + ISR);	/* clear pending IRQs */

	/* Master clock mode enabled above to allow reset commands
	 * to complete even if no data clocks are present.
	 *
	 * Disable master clock mode for normal communications because
	 * V3.2 of the ESCC2 has a bug that prevents the transmit all sent
	 * IRQ when in master clock mode.
	 *
	 * Leave master clock mode enabled for IRQ test because the
	 * timer IRQ used by the test can only happen in master clock mode.
	 */
	if (!info->testing_irq)
		clear_reg_bits(info, CHA + CCR0, BIT6);

	tx_set_idle(info);

	tx_stop(info);
	rx_stop(info);
}