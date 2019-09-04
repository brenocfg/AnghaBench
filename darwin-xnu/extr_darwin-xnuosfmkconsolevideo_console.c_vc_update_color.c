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
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {size_t v_depth; } ;

/* Variables and functions */
 void* vc_color_back ; 
 void* vc_color_fore ; 
 size_t* vc_color_index_table ; 
 void*** vc_colors ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void
vc_update_color(int color, boolean_t fore)
{
	if (!vinfo.v_depth)
		return;
	if (fore) {
        	vc_color_fore = vc_colors[color][vc_color_index_table[vinfo.v_depth]];
	} else {
		vc_color_back = vc_colors[color][vc_color_index_table[vinfo.v_depth]];
	}
}