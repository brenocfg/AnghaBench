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
typedef  int s32 ;
struct TYPE_4__ {int nonInter; } ;
struct TYPE_3__ {int hlw; int nhlines; int prbOdd; int equ; int psbOdd; int prbEven; int psbEven; } ;

/* Variables and functions */
 TYPE_2__ HorVer ; 
 TYPE_1__* currTiming ; 

__attribute__((used)) static void __VIDisplayPositionToXY(s32 xpos,s32 ypos,s32 *px,s32 *py)
{
	u32 hpos,vpos;
	u32 hline,val;

	hpos = (xpos-1);
	vpos = (ypos-1);
	hline = ((vpos<<1)+(hpos/currTiming->hlw));

	*px = (s32)hpos;
	if(HorVer.nonInter==0x0000) {
		if(hline<currTiming->nhlines) {
			val = currTiming->prbOdd+(currTiming->equ*3);
			if(hline>=val) {
				val = (currTiming->nhlines-currTiming->psbOdd);
				if(hline<val) {
					*py = (s32)(((hline-(currTiming->equ*3))-currTiming->prbOdd)&~0x01);
				} else
					*py = -1;
			} else
				*py = -1;
		} else {
			hline -= currTiming->psbOdd;
			val = (currTiming->prbEven+(currTiming->equ*3));
			if(hline>=val) {
				val = (currTiming->nhlines-currTiming->psbEven);
				if(hline<val) {
					*py = (s32)((((hline-(currTiming->equ*3))-currTiming->prbEven)&~0x01)+1);
				} else
					*py = -1;
			} else
				*py = -1;
		}
	} else if(HorVer.nonInter==0x0001) {
		if(hline>=currTiming->nhlines) hline -= currTiming->nhlines;

		val = (currTiming->prbOdd+(currTiming->equ*3));
		if(hline>=val) {
			val = (currTiming->nhlines-currTiming->psbOdd);
			if(hline<val) {
				*py = (s32)(((hline-(currTiming->equ*3))-currTiming->prbOdd)&~0x01);
			} else
				*py = -1;
		} else
			*py = -1;
	} else if(HorVer.nonInter==0x0002) {
		if(hline<currTiming->nhlines) {
			val = currTiming->prbOdd+(currTiming->equ*3);
			if(hline>=val) {
				val = (currTiming->nhlines-currTiming->psbOdd);
				if(hline<val) {
					*py = (s32)((hline-(currTiming->equ*3))-currTiming->prbOdd);
				} else
					*py = -1;
			} else
				*py = -1;
		} else {
			hline -= currTiming->psbOdd;
			val = (currTiming->prbEven+(currTiming->equ*3));
			if(hline>=val) {
				val = (currTiming->nhlines-currTiming->psbEven);
				if(hline<val) {
					*py = (s32)(((hline-(currTiming->equ*3))-currTiming->prbEven)&~0x01);
				} else
					*py = -1;
			} else
				*py = -1;
		}
	}
}