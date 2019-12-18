#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {scalar_t__ tx; } ;
struct TYPE_8__ {int tx_count; scalar_t__ tx_get; scalar_t__ max_frame_size; TYPE_1__ icount; scalar_t__* tx_buf; scalar_t__ x_char; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 int BIT1 ; 
 int /*<<< orphan*/  SR0 ; 
 int /*<<< orphan*/  TRB ; 
 int read_reg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_load_fifo(SLMP_INFO *info)
{
	u8 TwoBytes[2];

	/* do nothing is now tx data available and no XON/XOFF pending */

	if ( !info->tx_count && !info->x_char )
		return;

	/* load the Transmit FIFO until FIFOs full or all data sent */

	while( info->tx_count && (read_reg(info,SR0) & BIT1) ) {

		/* there is more space in the transmit FIFO and */
		/* there is more data in transmit buffer */

		if ( (info->tx_count > 1) && !info->x_char ) {
 			/* write 16-bits */
			TwoBytes[0] = info->tx_buf[info->tx_get++];
			if (info->tx_get >= info->max_frame_size)
				info->tx_get -= info->max_frame_size;
			TwoBytes[1] = info->tx_buf[info->tx_get++];
			if (info->tx_get >= info->max_frame_size)
				info->tx_get -= info->max_frame_size;

			write_reg16(info, TRB, *((u16 *)TwoBytes));

			info->tx_count -= 2;
			info->icount.tx += 2;
		} else {
			/* only 1 byte left to transmit or 1 FIFO slot left */

			if (info->x_char) {
				/* transmit pending high priority char */
				write_reg(info, TRB, info->x_char);
				info->x_char = 0;
			} else {
				write_reg(info, TRB, info->tx_buf[info->tx_get++]);
				if (info->tx_get >= info->max_frame_size)
					info->tx_get -= info->max_frame_size;
				info->tx_count--;
			}
			info->icount.tx++;
		}
	}
}