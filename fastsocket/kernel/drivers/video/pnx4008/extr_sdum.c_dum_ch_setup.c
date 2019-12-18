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
typedef  scalar_t__ u16 ;
struct dumchannel {int channelnr; scalar_t__ dum_ch_min; scalar_t__ dum_ch_max; int dum_ch_conf; int dum_ch_ctrl; int /*<<< orphan*/  member_0; } ;
struct dum_ch_setup {int disp_no; int format; int minadr; scalar_t__ maxadr; scalar_t__ xmin; scalar_t__ ymin; scalar_t__ xmax; scalar_t__ ymax; scalar_t__ dirtybuffer; scalar_t__ slave_trans; scalar_t__ rotate; scalar_t__ ymirror; scalar_t__ xmirror; } ;
struct disp_window {int xmin_l; int xmin_h; int ymin; int xmax_l; int xmax_h; int ymax; } ;
struct cmdstring {int channelnr; int prestringlen; int poststringlen; int reserved; int startaddr_low; int startaddr_high; int pixdatlen_low; int pixdatlen_high; void** postcmd; void** precmd; scalar_t__ format; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DISP_1_REG ; 
 int /*<<< orphan*/  DISP_DUMMY1_REG ; 
 int /*<<< orphan*/  DISP_PIXEL_REG ; 
 int /*<<< orphan*/  DISP_XMAX_H_REG ; 
 int /*<<< orphan*/  DISP_XMAX_L_REG ; 
 int /*<<< orphan*/  DISP_XMIN_H_REG ; 
 int /*<<< orphan*/  DISP_XMIN_L_REG ; 
 int /*<<< orphan*/  DISP_YMAX_REG ; 
 int /*<<< orphan*/  DISP_YMIN_REG ; 
 void* build_command (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_disp_window (struct dum_ch_setup*,struct disp_window*) ; 
 void* build_double_index (int,int /*<<< orphan*/ ) ; 
 int nof_bytes (struct dum_ch_setup*) ; 
 int /*<<< orphan*/  put_channel (struct dumchannel) ; 
 int put_cmd_string (struct cmdstring) ; 

__attribute__((used)) static u32 dum_ch_setup(int ch_no, struct dum_ch_setup * ch_setup)
{
	struct cmdstring cmds_c;
	struct cmdstring *cmds = &cmds_c;
	struct disp_window dw;
	int standard;
	u32 orientation = 0;
	struct dumchannel chan = { 0 };
	int ret;

	if ((ch_setup->xmirror) || (ch_setup->ymirror) || (ch_setup->rotate)) {
		standard = 0;

		orientation = BIT(1);	/* always set 9-bit-bus */
		if (ch_setup->xmirror)
			orientation |= BIT(4);
		if (ch_setup->ymirror)
			orientation |= BIT(3);
		if (ch_setup->rotate)
			orientation |= BIT(0);
	} else
		standard = 1;

	cmds->channelnr = ch_no;

	/* build command string header */
	if (standard) {
		cmds->prestringlen = 32;
		cmds->poststringlen = 0;
	} else {
		cmds->prestringlen = 48;
		cmds->poststringlen = 16;
	}

	cmds->format =
	    (u16) ((ch_setup->disp_no << 4) | (BIT(3)) | (ch_setup->format));
	cmds->reserved = 0x0;
	cmds->startaddr_low = (ch_setup->minadr & 0xFFFF);
	cmds->startaddr_high = (ch_setup->minadr >> 16);

	if ((ch_setup->minadr == 0) && (ch_setup->maxadr == 0)
	    && (ch_setup->xmin == 0)
	    && (ch_setup->ymin == 0) && (ch_setup->xmax == 0)
	    && (ch_setup->ymax == 0)) {
		cmds->pixdatlen_low = 0;
		cmds->pixdatlen_high = 0;
	} else {
		u32 nbytes = nof_bytes(ch_setup);
		cmds->pixdatlen_low = (nbytes & 0xFFFF);
		cmds->pixdatlen_high = (nbytes >> 16);
	}

	if (ch_setup->slave_trans)
		cmds->pixdatlen_high |= BIT(15);

	/* build pre-string */
	build_disp_window(ch_setup, &dw);

	if (standard) {
		cmds->precmd[0] =
		    build_command(ch_setup->disp_no, DISP_XMIN_L_REG, 0x99);
		cmds->precmd[1] =
		    build_command(ch_setup->disp_no, DISP_XMIN_L_REG,
				  dw.xmin_l);
		cmds->precmd[2] =
		    build_command(ch_setup->disp_no, DISP_XMIN_H_REG,
				  dw.xmin_h);
		cmds->precmd[3] =
		    build_command(ch_setup->disp_no, DISP_YMIN_REG, dw.ymin);
		cmds->precmd[4] =
		    build_command(ch_setup->disp_no, DISP_XMAX_L_REG,
				  dw.xmax_l);
		cmds->precmd[5] =
		    build_command(ch_setup->disp_no, DISP_XMAX_H_REG,
				  dw.xmax_h);
		cmds->precmd[6] =
		    build_command(ch_setup->disp_no, DISP_YMAX_REG, dw.ymax);
		cmds->precmd[7] =
		    build_double_index(ch_setup->disp_no, DISP_PIXEL_REG);
	} else {
		if (dw.xmin_l == ch_no)
			cmds->precmd[0] =
			    build_command(ch_setup->disp_no, DISP_XMIN_L_REG,
					  0x99);
		else
			cmds->precmd[0] =
			    build_command(ch_setup->disp_no, DISP_XMIN_L_REG,
					  ch_no);

		cmds->precmd[1] =
		    build_command(ch_setup->disp_no, DISP_XMIN_L_REG,
				  dw.xmin_l);
		cmds->precmd[2] =
		    build_command(ch_setup->disp_no, DISP_XMIN_H_REG,
				  dw.xmin_h);
		cmds->precmd[3] =
		    build_command(ch_setup->disp_no, DISP_YMIN_REG, dw.ymin);
		cmds->precmd[4] =
		    build_command(ch_setup->disp_no, DISP_XMAX_L_REG,
				  dw.xmax_l);
		cmds->precmd[5] =
		    build_command(ch_setup->disp_no, DISP_XMAX_H_REG,
				  dw.xmax_h);
		cmds->precmd[6] =
		    build_command(ch_setup->disp_no, DISP_YMAX_REG, dw.ymax);
		cmds->precmd[7] =
		    build_command(ch_setup->disp_no, DISP_1_REG, orientation);
		cmds->precmd[8] =
		    build_double_index(ch_setup->disp_no, DISP_PIXEL_REG);
		cmds->precmd[9] =
		    build_double_index(ch_setup->disp_no, DISP_PIXEL_REG);
		cmds->precmd[0xA] =
		    build_double_index(ch_setup->disp_no, DISP_PIXEL_REG);
		cmds->precmd[0xB] =
		    build_double_index(ch_setup->disp_no, DISP_PIXEL_REG);
		cmds->postcmd[0] =
		    build_command(ch_setup->disp_no, DISP_1_REG, BIT(1));
		cmds->postcmd[1] =
		    build_command(ch_setup->disp_no, DISP_DUMMY1_REG, 1);
		cmds->postcmd[2] =
		    build_command(ch_setup->disp_no, DISP_DUMMY1_REG, 2);
		cmds->postcmd[3] =
		    build_command(ch_setup->disp_no, DISP_DUMMY1_REG, 3);
	}

	if ((ret = put_cmd_string(cmds_c)) != 0) {
		return ret;
	}

	chan.channelnr = cmds->channelnr;
	chan.dum_ch_min = ch_setup->dirtybuffer + ch_setup->minadr;
	chan.dum_ch_max = ch_setup->dirtybuffer + ch_setup->maxadr;
	chan.dum_ch_conf = 0x002;
	chan.dum_ch_ctrl = 0x04;

	put_channel(chan);

	return 0;
}