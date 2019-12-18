#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int clock_speed; } ;
struct TYPE_11__ {int port_num; TYPE_2__ params; TYPE_1__** port_array; } ;
struct TYPE_9__ {int ctrlreg_value; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 int /*<<< orphan*/  MD2 ; 
 int /*<<< orphan*/  RXS ; 
 int /*<<< orphan*/  TXS ; 
 int read_reg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rate (TYPE_3__*,int) ; 
 int /*<<< orphan*/  write_control_reg (TYPE_3__*) ; 
 int /*<<< orphan*/  write_reg (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_loopback(SLMP_INFO *info, int enable)
{
	if (enable) {
		/* MD2 (Mode Register 2)
		 * 01..00  CNCT<1..0> Channel Connection 11=Local Loopback
		 */
		write_reg(info, MD2, (unsigned char)(read_reg(info, MD2) | (BIT1 + BIT0)));

		/* degate external TxC clock source */
		info->port_array[0]->ctrlreg_value |= (BIT0 << (info->port_num * 2));
		write_control_reg(info);

		/* RXS/TXS (Rx/Tx clock source)
		 * 07      Reserved, must be 0
		 * 06..04  Clock Source, 100=BRG
		 * 03..00  Clock Divisor, 0000=1
		 */
		write_reg(info, RXS, 0x40);
		write_reg(info, TXS, 0x40);

	} else {
		/* MD2 (Mode Register 2)
	 	 * 01..00  CNCT<1..0> Channel connection, 0=normal
		 */
		write_reg(info, MD2, (unsigned char)(read_reg(info, MD2) & ~(BIT1 + BIT0)));

		/* RXS/TXS (Rx/Tx clock source)
		 * 07      Reserved, must be 0
		 * 06..04  Clock Source, 000=RxC/TxC Pin
		 * 03..00  Clock Divisor, 0000=1
		 */
		write_reg(info, RXS, 0x00);
		write_reg(info, TXS, 0x00);
	}

	/* set LinkSpeed if available, otherwise default to 2Mbps */
	if (info->params.clock_speed)
		set_rate(info, info->params.clock_speed);
	else
		set_rate(info, 3686400);
}