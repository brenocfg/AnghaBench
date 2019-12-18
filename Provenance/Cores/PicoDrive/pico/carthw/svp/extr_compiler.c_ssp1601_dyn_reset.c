#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_7__ {int iram_dirty; void* ptr_btable_iram; void* ptr_btable; void* ptr_dram; void* ptr_iram_rom; void* ptr_rom; scalar_t__ iram_context; } ;
struct TYPE_8__ {TYPE_1__ drc; } ;
typedef  TYPE_2__ ssp1601_t ;
struct TYPE_10__ {scalar_t__ rom; } ;
struct TYPE_9__ {scalar_t__ iram_rom; scalar_t__ dram; } ;

/* Variables and functions */
 TYPE_6__ Pico ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssp1601_reset (TYPE_2__*) ; 
 scalar_t__ ssp_block_table ; 
 scalar_t__ ssp_block_table_iram ; 
 TYPE_3__* svp ; 

void ssp1601_dyn_reset(ssp1601_t *ssp)
{
	ssp1601_reset(ssp);
	ssp->drc.iram_dirty = 1;
	ssp->drc.iram_context = 0;
	// must do this here because ssp is not available @ startup()
	ssp->drc.ptr_rom = (u32) Pico.rom;
	ssp->drc.ptr_iram_rom = (u32) svp->iram_rom;
	ssp->drc.ptr_dram = (u32) svp->dram;
	ssp->drc.ptr_btable = (u32) ssp_block_table;
	ssp->drc.ptr_btable_iram = (u32) ssp_block_table_iram;

	// prevent new versions of IRAM from appearing
	memset(svp->iram_rom, 0, 0x800);
}