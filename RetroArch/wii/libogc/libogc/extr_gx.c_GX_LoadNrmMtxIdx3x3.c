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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int U8; int U32; } ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* wgPipe ; 

void GX_LoadNrmMtxIdx3x3(u16 mtxidx,u32 pnidx)
{
	wgPipe->U8 = 0x28;
	wgPipe->U32 = ((_SHIFTL(mtxidx,16,16))|0x8000|(0x0400|(pnidx*3)));
}