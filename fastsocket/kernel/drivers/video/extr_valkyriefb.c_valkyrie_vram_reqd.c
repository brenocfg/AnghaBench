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
struct valkyrie_regvals {int* pitch; int vres; } ;

/* Variables and functions */
 struct valkyrie_regvals** valkyrie_reg_init ; 

__attribute__((used)) static inline int valkyrie_vram_reqd(int video_mode, int color_mode)
{
	int pitch;
	struct valkyrie_regvals *init = valkyrie_reg_init[video_mode-1];
	
	if ((pitch = init->pitch[color_mode]) == 0)
		pitch = 2 * init->pitch[0];
	return init->vres * pitch;
}