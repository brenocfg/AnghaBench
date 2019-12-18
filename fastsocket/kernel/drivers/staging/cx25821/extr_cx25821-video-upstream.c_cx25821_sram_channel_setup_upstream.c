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
typedef  int u32 ;
struct sram_channel {scalar_t__ cmds_start; int ptr1_reg; int ptr2_reg; int cnt2_reg; int cnt1_reg; int cdt; unsigned int fifo_size; unsigned int fifo_start; unsigned int ctrl_start; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int VID_IQ_SIZE_DW ; 
 int /*<<< orphan*/  cx_write (int,unsigned int) ; 

int cx25821_sram_channel_setup_upstream(struct cx25821_dev *dev,
					struct sram_channel *ch,
					unsigned int bpl, u32 risc)
{
	unsigned int i, lines;
	u32 cdt;

	if (ch->cmds_start == 0) {
		cx_write(ch->ptr1_reg, 0);
		cx_write(ch->ptr2_reg, 0);
		cx_write(ch->cnt2_reg, 0);
		cx_write(ch->cnt1_reg, 0);
		return 0;
	}

	bpl = (bpl + 7) & ~7;	/* alignment */
	cdt = ch->cdt;
	lines = ch->fifo_size / bpl;

	if (lines > 4) {
		lines = 4;
	}

	BUG_ON(lines < 2);

	/* write CDT */
	for (i = 0; i < lines; i++) {
		cx_write(cdt + 16 * i, ch->fifo_start + bpl * i);
		cx_write(cdt + 16 * i + 4, 0);
		cx_write(cdt + 16 * i + 8, 0);
		cx_write(cdt + 16 * i + 12, 0);
	}

	/* write CMDS */
	cx_write(ch->cmds_start + 0, risc);

	cx_write(ch->cmds_start + 4, 0);
	cx_write(ch->cmds_start + 8, cdt);
	cx_write(ch->cmds_start + 12, (lines * 16) >> 3);
	cx_write(ch->cmds_start + 16, ch->ctrl_start);

	cx_write(ch->cmds_start + 20, VID_IQ_SIZE_DW);

	for (i = 24; i < 80; i += 4)
		cx_write(ch->cmds_start + i, 0);

	/* fill registers */
	cx_write(ch->ptr1_reg, ch->fifo_start);
	cx_write(ch->ptr2_reg, cdt);
	cx_write(ch->cnt2_reg, (lines * 16) >> 3);
	cx_write(ch->cnt1_reg, (bpl >> 3) - 1);

	return 0;
}