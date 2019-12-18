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
typedef  int /*<<< orphan*/  Mtx33 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_XF_REGS (int,int) ; 
 int /*<<< orphan*/  WriteMtxPS3x3 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ wgPipe ; 

void GX_LoadNrmMtxImm3x3(Mtx33 mt,u32 pnidx)
{
	GX_LOAD_XF_REGS((0x0400|(pnidx*3)),9);
	WriteMtxPS3x3(mt,(void*)wgPipe);
}