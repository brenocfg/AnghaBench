#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; int clock_speed; } ;
struct TYPE_7__ {TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned char BIT2 ; 
 scalar_t__ CCR0 ; 
 scalar_t__ CCR1 ; 
 scalar_t__ CCR2 ; 
 scalar_t__ CCR4 ; 
 scalar_t__ CHB ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MODE ; 
 int /*<<< orphan*/  mgslpc_set_rate (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,int) ; 

__attribute__((used)) static void enable_auxclk(MGSLPC_INFO *info)
{
	unsigned char val;

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

	/* channel B RTS is used to enable AUXCLK driver on SP505 */
	if (info->params.mode == MGSL_MODE_HDLC && info->params.clock_speed)
		val |= BIT2;
	write_reg(info, CHB + MODE, val);

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
	write_reg(info, CHB + CCR0, 0xc0);

	/* CCR1
	 *
	 * 07      SFLG Shared Flag, 0 = disable shared flags
	 * 06      GALP Go Active On Loop, 0 = not used
	 * 05      GLP Go On Loop, 0 = not used
	 * 04      ODS Output Driver Select, 1=TxD is push-pull output
	 * 03      ITF Interframe Time Fill, 0=mark, 1=flag
	 * 02..00  CM[2..0] Clock Mode
	 *
	 * 0001 0111
	 */
	write_reg(info, CHB + CCR1, 0x17);

	/* CCR2 (Channel B)
	 *
	 * 07..06  BGR[9..8] Baud rate bits 9..8
	 * 05      BDF Baud rate divisor factor, 0=1, 1=BGR value
	 * 04      SSEL Clock source select, 1=submode b
	 * 03      TOE 0=TxCLK is input, 1=TxCLK is output
	 * 02      RWX Read/Write Exchange 0=disabled
	 * 01      C32, CRC select, 0=CRC-16, 1=CRC-32
	 * 00      DIV, data inversion 0=disabled, 1=enabled
	 *
	 * 0011 1000
	 */
	if (info->params.mode == MGSL_MODE_HDLC && info->params.clock_speed)
		write_reg(info, CHB + CCR2, 0x38);
	else
		write_reg(info, CHB + CCR2, 0x30);

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
	write_reg(info, CHB + CCR4, 0x50);

	/* if auxclk not enabled, set internal BRG so
	 * CTS transitions can be detected (requires TxC)
	 */
	if (info->params.mode == MGSL_MODE_HDLC && info->params.clock_speed)
		mgslpc_set_rate(info, CHB, info->params.clock_speed);
	else
		mgslpc_set_rate(info, CHB, 921600);
}