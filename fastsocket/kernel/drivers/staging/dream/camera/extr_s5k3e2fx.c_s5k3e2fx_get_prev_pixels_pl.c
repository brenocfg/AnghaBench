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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ blk_p; scalar_t__ size_w; } ;

/* Variables and functions */
 size_t S_RES_PREVIEW ; 
 TYPE_1__* s5k3e2fx_reg_pat ; 

__attribute__((used)) static uint16_t s5k3e2fx_get_prev_pixels_pl(void)
{
	return (s5k3e2fx_reg_pat[S_RES_PREVIEW].size_w +
		s5k3e2fx_reg_pat[S_RES_PREVIEW].blk_p);
}