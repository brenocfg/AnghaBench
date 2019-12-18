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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int size_h; int blk_l; int size_w; int blk_p; } ;

/* Variables and functions */
 size_t S_RES_CAPTURE ; 
 size_t S_RES_PREVIEW ; 
 TYPE_1__* s5k3e2fx_reg_pat ; 

__attribute__((used)) static void s5k3e2fx_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
	/* input fps is preview fps in Q8 format */
	uint32_t divider;   /* Q10 */

	divider = (uint32_t)
		((s5k3e2fx_reg_pat[S_RES_PREVIEW].size_h +
			s5k3e2fx_reg_pat[S_RES_PREVIEW].blk_l) *
		 (s5k3e2fx_reg_pat[S_RES_PREVIEW].size_w +
			s5k3e2fx_reg_pat[S_RES_PREVIEW].blk_p)) * 0x00000400 /
		((s5k3e2fx_reg_pat[S_RES_CAPTURE].size_h +
			s5k3e2fx_reg_pat[S_RES_CAPTURE].blk_l) *
		 (s5k3e2fx_reg_pat[S_RES_CAPTURE].size_w +
			s5k3e2fx_reg_pat[S_RES_CAPTURE].blk_p));

	/* Verify PCLK settings and frame sizes. */
	*pfps = (uint16_t)(fps * divider / 0x00000400);
}