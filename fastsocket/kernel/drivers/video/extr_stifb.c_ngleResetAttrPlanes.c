#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int xres; int yres; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct stifb_info {scalar_t__ id; TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddrLong ; 
 int /*<<< orphan*/  BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAIndexBase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAJustPoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINattr ; 
 int /*<<< orphan*/  BitmapExtent08 ; 
 int /*<<< orphan*/  DataDynamic ; 
 int /*<<< orphan*/  FGx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_FIFO_SLOTS (struct stifb_info*,int,int) ; 
 int /*<<< orphan*/  IBOvals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexedDcd ; 
 int /*<<< orphan*/  MaskAddrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaskOtc ; 
 int /*<<< orphan*/  NGLE_LOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_CTL_PLN_REG (struct stifb_info*,unsigned int) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_DST_BM_ACCESS (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_IMAGE_BITMAP_OP (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_SET_DSTXY (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_SET_TRANSFERDATA (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_UNLOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  Otc32 ; 
 int /*<<< orphan*/  OtsIndirect ; 
 int /*<<< orphan*/  RopSrc ; 
 scalar_t__ S9000_ID_A1659A ; 
 int /*<<< orphan*/  SET_LENXY_START_RECFILL (struct stifb_info*,int) ; 
 int /*<<< orphan*/  StaticReg (int) ; 

__attribute__((used)) static void
ngleResetAttrPlanes(struct stifb_info *fb, unsigned int ctlPlaneReg)
{
	int nFreeFifoSlots = 0;
	u32 packed_dst;
	u32 packed_len;

	NGLE_LOCK(fb);

	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 4);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
				     BA(IndexedDcd, Otc32, OtsIndirect,
					AddrLong, BAJustPoint(0),
					BINattr, BAIndexBase(0)));
	NGLE_QUICK_SET_CTL_PLN_REG(fb, ctlPlaneReg);
	NGLE_SET_TRANSFERDATA(fb, 0xffffffff);

	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvals(RopSrc, MaskAddrOffset(0),
					       BitmapExtent08, StaticReg(1),
					       DataDynamic, MaskOtc,
					       BGx(0), FGx(0)));
	packed_dst = 0;
	packed_len = (fb->info.var.xres << 16) | fb->info.var.yres;
	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 2);
	NGLE_SET_DSTXY(fb, packed_dst);
	SET_LENXY_START_RECFILL(fb, packed_len);

	/*
	 * In order to work around an ELK hardware problem (Buffy doesn't
	 * always flush it's buffers when writing to the attribute
	 * planes), at least 4 pixels must be written to the attribute
	 * planes starting at (X == 1280) and (Y != to the last Y written
	 * by BIF):
	 */

	if (fb->id == S9000_ID_A1659A) {   /* ELK_DEVICE_ID */
		/* It's safe to use scanline zero: */
		packed_dst = (1280 << 16);
		GET_FIFO_SLOTS(fb, nFreeFifoSlots, 2);
		NGLE_SET_DSTXY(fb, packed_dst);
		packed_len = (4 << 16) | 1;
		SET_LENXY_START_RECFILL(fb, packed_len);
	}   /* ELK Hardware Kludge */

	/**** Finally, set the Control Plane Register back to zero: ****/
	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 1);
	NGLE_QUICK_SET_CTL_PLN_REG(fb, 0);
	
	NGLE_UNLOCK(fb);
}