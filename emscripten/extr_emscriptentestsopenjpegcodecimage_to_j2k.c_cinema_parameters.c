#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tile_size_on; int cp_tdx; int cp_tdy; char tp_flag; int tp_on; int cblockw_init; int cblockh_init; int csty; int roi_compno; int subsampling_dx; int subsampling_dy; int irreversible; int /*<<< orphan*/  prog_order; scalar_t__ image_offset_y0; scalar_t__ image_offset_x0; scalar_t__ cp_ty0; scalar_t__ cp_tx0; } ;
typedef  TYPE_1__ opj_cparameters_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPRL ; 

void cinema_parameters(opj_cparameters_t *parameters){
	parameters->tile_size_on = false;
	parameters->cp_tdx=1;
	parameters->cp_tdy=1;

	/*Tile part*/
	parameters->tp_flag = 'C';
	parameters->tp_on = 1;

	/*Tile and Image shall be at (0,0)*/
	parameters->cp_tx0 = 0;
	parameters->cp_ty0 = 0;
	parameters->image_offset_x0 = 0;
	parameters->image_offset_y0 = 0;

	/*Codeblock size= 32*32*/
	parameters->cblockw_init = 32;
	parameters->cblockh_init = 32;
	parameters->csty |= 0x01;

	/*The progression order shall be CPRL*/
	parameters->prog_order = CPRL;

	/* No ROI */
	parameters->roi_compno = -1;

	parameters->subsampling_dx = 1;		parameters->subsampling_dy = 1;

	/* 9-7 transform */
	parameters->irreversible = 1;

}