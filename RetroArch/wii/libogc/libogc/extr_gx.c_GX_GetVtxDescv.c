#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_5__ {int vcdLo; int vcdNrms; int vcdHi; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__ GXVtxDesc ;

/* Variables and functions */
 size_t GX_MAX_VTXDESC_LISTSIZE ; 
 int /*<<< orphan*/  GX_VA_CLR0 ; 
 int /*<<< orphan*/  GX_VA_CLR1 ; 
 int /*<<< orphan*/  GX_VA_NBT ; 
 int /*<<< orphan*/  GX_VA_NRM ; 
 int /*<<< orphan*/  GX_VA_NULL ; 
 int /*<<< orphan*/  GX_VA_POS ; 
 int /*<<< orphan*/  GX_VA_PTNMTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX0 ; 
 int /*<<< orphan*/  GX_VA_TEX0MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX1 ; 
 int /*<<< orphan*/  GX_VA_TEX1MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX2 ; 
 int /*<<< orphan*/  GX_VA_TEX2MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX3 ; 
 int /*<<< orphan*/  GX_VA_TEX3MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX4 ; 
 int /*<<< orphan*/  GX_VA_TEX4MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX5 ; 
 int /*<<< orphan*/  GX_VA_TEX5MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX6 ; 
 int /*<<< orphan*/  GX_VA_TEX6MTXIDX ; 
 int /*<<< orphan*/  GX_VA_TEX7 ; 
 int /*<<< orphan*/  GX_VA_TEX7MTXIDX ; 
 void* _SHIFTR (int,int,int) ; 
 TYPE_2__* __gx ; 

void GX_GetVtxDescv(GXVtxDesc *attr_list)
{
	u32 count;

	// Clear everything first
	for(count=0;count<GX_MAX_VTXDESC_LISTSIZE;count++) {
		attr_list[count].attr = GX_VA_NULL;
		attr_list[count].type = 0;
	}

	count = 0;
	if(__gx->vcdLo&0x1) {
		attr_list[count].attr = GX_VA_PTNMTXIDX;
		attr_list[count].type = __gx->vcdLo&0x1;
		count++;
	}

	if(__gx->vcdLo&0x2) {
		attr_list[count].attr = GX_VA_TEX0MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x2,1,1);
		count++;
	}

	if(__gx->vcdLo&0x4) {
		attr_list[count].attr = GX_VA_TEX1MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x4,2,1);
		count++;
	}

	if(__gx->vcdLo&0x8) {
		attr_list[count].attr = GX_VA_TEX2MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x8,3,1);
		count++;
	}

	if(__gx->vcdLo&0x10) {
		attr_list[count].attr = GX_VA_TEX3MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x10,4,1);
		count++;
	}

	if(__gx->vcdLo&0x20) {
		attr_list[count].attr = GX_VA_TEX4MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x20,5,1);
		count++;
	}

	if(__gx->vcdLo&0x40) {
		attr_list[count].attr = GX_VA_TEX5MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x40,6,1);
		count++;
	}

	if(__gx->vcdLo&0x80) {
		attr_list[count].attr = GX_VA_TEX6MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x80,7,1);
		count++;
	}

	if(__gx->vcdLo&0x100) {
		attr_list[count].attr = GX_VA_TEX7MTXIDX;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x100,8,1);
		count++;
	}

	if(__gx->vcdLo&0x600) {
		attr_list[count].attr = GX_VA_POS;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x600,9,2);
		count++;
	}

	if(__gx->vcdLo&0x1800) {
		if(__gx->vcdNrms==1) {
			attr_list[count].attr = GX_VA_NRM;
			attr_list[count].type = _SHIFTR(__gx->vcdLo&0x1800,11,2);
			count++;
		} else if(__gx->vcdNrms==2){
			attr_list[count].attr = GX_VA_NBT;
			attr_list[count].type = _SHIFTR(__gx->vcdLo&0x1800,11,2);
			count++;
		}
	}

	if(__gx->vcdLo&0x6000) {
		attr_list[count].attr = GX_VA_CLR0;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x6000,13,2);
		count++;
	}

	if(__gx->vcdLo&0x18000) {
		attr_list[count].attr = GX_VA_CLR1;
		attr_list[count].type = _SHIFTR(__gx->vcdLo&0x18000,15,2);
		count++;
	}

	if(__gx->vcdHi&0x3) {
		attr_list[count].attr = GX_VA_TEX0;
		attr_list[count].type = __gx->vcdHi&0x3;
		count++;
	}

	if(__gx->vcdHi&0xc) {
		attr_list[count].attr = GX_VA_TEX1;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0xc,2,2);
		count++;
	}

	if(__gx->vcdHi&0x30) {
		attr_list[count].attr = GX_VA_TEX2;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0x30,4,2);
		count++;
	}

	if(__gx->vcdHi&0xc0) {
		attr_list[count].attr = GX_VA_TEX3;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0xc0,6,2);
		count++;
	}

	if(__gx->vcdHi&0x300) {
		attr_list[count].attr = GX_VA_TEX4;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0x300,8,2);
		count++;
	}

	if(__gx->vcdHi&0xc00) {
		attr_list[count].attr = GX_VA_TEX5;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0xc00,10,2);
		count++;
	}

	if(__gx->vcdHi&0x3000) {
		attr_list[count].attr = GX_VA_TEX6;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0x3000,12,2);
		count++;
	}

	if(__gx->vcdHi&0xc000) {
		attr_list[count].attr = GX_VA_TEX7;
		attr_list[count].type = _SHIFTR(__gx->vcdHi&0xc000,14,2);
		count++;
	}
}