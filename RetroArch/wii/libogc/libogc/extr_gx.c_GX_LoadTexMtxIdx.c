#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int U8; scalar_t__ U32; } ;

/* Variables and functions */
 scalar_t__ GX_DTTMTX0 ; 
 scalar_t__ GX_MTX2x4 ; 
 scalar_t__ _SHIFTL (scalar_t__,int,int) ; 
 TYPE_1__* wgPipe ; 

void GX_LoadTexMtxIdx(u16 mtxidx,u32 texidx,u8 type)
{
	u32 addr,size = (type==GX_MTX2x4)?7:11;

	if(texidx<GX_DTTMTX0) addr = 0x0000|(_SHIFTL(texidx,2,8));
	else addr = 0x0500|(_SHIFTL((texidx-GX_DTTMTX0),2,8));

	wgPipe->U8 = 0x30;
	wgPipe->U32 = ((_SHIFTL(mtxidx,16,16))|(_SHIFTL(size,12,4))|addr);
}