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
struct TYPE_3__ {int cp_tdx; int cp_tdy; char tp_flag; int tp_on; int cblockw_init; int cblockh_init; int csty; int roi_compno; int subsampling_dx; int subsampling_dy; int irreversible; int tcp_mct; int /*<<< orphan*/  prog_order; scalar_t__ image_offset_y0; scalar_t__ image_offset_x0; scalar_t__ cp_ty0; scalar_t__ cp_tx0; scalar_t__ tile_size_on; } ;
typedef  TYPE_1__ opj_cparameters_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_CPRL ; 

__attribute__((used)) static void cinema_parameters(opj_cparameters_t *p)
{
    p->tile_size_on = 0;
    p->cp_tdx = 1;
    p->cp_tdy = 1;

    /* Tile part */
    p->tp_flag = 'C';
    p->tp_on = 1;

    /* Tile and Image shall be at (0, 0) */
    p->cp_tx0 = 0;
    p->cp_ty0 = 0;
    p->image_offset_x0 = 0;
    p->image_offset_y0 = 0;

    /* Codeblock size= 32 * 32 */
    p->cblockw_init = 32;
    p->cblockh_init = 32;
    p->csty |= 0x01;

    /* The progression order shall be CPRL */
    p->prog_order = OPJ_CPRL;

    /* No ROI */
    p->roi_compno = -1;

    /* No subsampling */
    p->subsampling_dx = 1;
    p->subsampling_dy = 1;

    /* 9-7 transform */
    p->irreversible = 1;

    p->tcp_mct = 1;
}