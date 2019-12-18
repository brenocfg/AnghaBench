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
struct TYPE_2__ {int ubo_l; int ubo_h; int vbo_l; int vbo_h; } ;
union chan_param_mem {TYPE_1__ pp; } ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void ipu_ch_param_set_plane_offset(union chan_param_mem *params,
					  u32 u_offset, u32 v_offset)
{
	params->pp.ubo_l = u_offset & 0x7ff;
	params->pp.ubo_h = u_offset >> 11;
	params->pp.vbo_l = v_offset & 0x1ffff;
	params->pp.vbo_h = v_offset >> 17;
}