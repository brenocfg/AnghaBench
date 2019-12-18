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
typedef  scalar_t__ u32 ;
struct sram_channel {scalar_t__ cmds_start; scalar_t__ ptr1_reg; scalar_t__ ptr2_reg; scalar_t__ cnt2_reg; scalar_t__ cnt1_reg; scalar_t__ cdt; unsigned int fifo_size; scalar_t__ fifo_start; scalar_t__ ctrl_start; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUDIO_CDT_SIZE_QW ; 
 scalar_t__ AUDIO_CLUSTER_SIZE_QW ; 
 scalar_t__ AUDIO_IQ_SIZE_DW ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cx_write (scalar_t__,scalar_t__) ; 

int cx25821_sram_channel_setup_upstream_audio(struct cx25821_dev *dev,
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

	if (lines > 3) {
		lines = 3;
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
	cx_write(ch->cmds_start + 12, AUDIO_CDT_SIZE_QW);
	cx_write(ch->cmds_start + 16, ch->ctrl_start);

	//IQ size
	cx_write(ch->cmds_start + 20, AUDIO_IQ_SIZE_DW);

	for (i = 24; i < 80; i += 4)
		cx_write(ch->cmds_start + i, 0);

	/* fill registers */
	cx_write(ch->ptr1_reg, ch->fifo_start);
	cx_write(ch->ptr2_reg, cdt);
	cx_write(ch->cnt2_reg, AUDIO_CDT_SIZE_QW);
	cx_write(ch->cnt1_reg, AUDIO_CLUSTER_SIZE_QW - 1);

	return 0;
}