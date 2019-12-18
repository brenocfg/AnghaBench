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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ gxFifoUnlinked; scalar_t__ saveDLctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX_GetCPUFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX_GetFifoCount (int /*<<< orphan*/ *) ; 
 scalar_t__ GX_GetFifoWrap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX_SetCPUFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRUCT_REGDEF_SIZE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 TYPE_1__* __gx ; 
 int /*<<< orphan*/  __gxregs ; 
 int /*<<< orphan*/  _gx_dl_fifoobj ; 
 int /*<<< orphan*/  _gx_old_cpufifo ; 
 int /*<<< orphan*/  _gx_saved_data ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 GX_EndDispList()
{
	u32 level;
	u8 wrap = 0;

	GX_GetCPUFifo(&_gx_dl_fifoobj);
	GX_SetCPUFifo(&_gx_old_cpufifo);

	if(__gx->saveDLctx) {
		_CPU_ISR_Disable(level);
		memcpy(__gxregs,_gx_saved_data,STRUCT_REGDEF_SIZE);
		_CPU_ISR_Restore(level);
	}

	__gx->gxFifoUnlinked = 0;

	wrap = GX_GetFifoWrap(&_gx_dl_fifoobj);
	if(wrap) return 0;

	return GX_GetFifoCount(&_gx_dl_fifoobj);
}