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
struct intelfb_info {int fb_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int COLOR_DEPTH_16 ; 
 int COLOR_DEPTH_32 ; 
 int COLOR_DEPTH_8 ; 
 int /*<<< orphan*/  DBG_MSG (char*,int,int,int,int,int,int,int,int) ; 
 int HEIGHT_SHIFT ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int PITCH_SHIFT ; 
 int ROP_SHIFT ; 
 int SRC_ROP_GXCOPY ; 
 int /*<<< orphan*/  START_RING (int) ; 
 int WIDTH_SHIFT ; 
 int WRITE_ALPHA ; 
 int WRITE_RGB ; 
 int XY_SRC_COPY_BLT_CMD ; 

void
intelfbhw_do_bitblt(struct intelfb_info *dinfo, u32 curx, u32 cury,
		    u32 dstx, u32 dsty, u32 w, u32 h, u32 pitch, u32 bpp)
{
	u32 br00, br09, br11, br12, br13, br22, br23, br26;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_do_bitblt: (%d,%d)->(%d,%d) %dx%d, p %d bpp %d\n",
		curx, cury, dstx, dsty, w, h, pitch, bpp);
#endif

	br00 = XY_SRC_COPY_BLT_CMD;
	br09 = dinfo->fb_start;
	br11 = (pitch << PITCH_SHIFT);
	br12 = dinfo->fb_start;
	br13 = (SRC_ROP_GXCOPY << ROP_SHIFT) | (pitch << PITCH_SHIFT);
	br22 = (dstx << WIDTH_SHIFT) | (dsty << HEIGHT_SHIFT);
	br23 = ((dstx + w) << WIDTH_SHIFT) |
	       ((dsty + h) << HEIGHT_SHIFT);
	br26 = (curx << WIDTH_SHIFT) | (cury << HEIGHT_SHIFT);

	switch (bpp) {
	case 8:
		br13 |= COLOR_DEPTH_8;
		break;
	case 16:
		br13 |= COLOR_DEPTH_16;
		break;
	case 32:
		br13 |= COLOR_DEPTH_32;
		br00 |= WRITE_ALPHA | WRITE_RGB;
		break;
	}

	START_RING(8);
	OUT_RING(br00);
	OUT_RING(br13);
	OUT_RING(br22);
	OUT_RING(br23);
	OUT_RING(br09);
	OUT_RING(br26);
	OUT_RING(br11);
	OUT_RING(br12);
	ADVANCE_RING();
}