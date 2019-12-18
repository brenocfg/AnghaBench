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
typedef  void* uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  Vdp2DrawBackScreen () ; 
 int /*<<< orphan*/  Vdp2DrawLineColorScreen () ; 
 void* cur_addr ; 
 void* cur_vdp2 ; 
 int /*<<< orphan*/  pvr_scene_begin () ; 
 int /*<<< orphan*/  pvr_wait_ready () ; 
 scalar_t__ tex_space ; 
 scalar_t__ vdp2_tex ; 

__attribute__((used)) static void VIDDCVdp2DrawStart(void)    {
    cur_addr = (uint32) tex_space;
    cur_vdp2 = (uint32) vdp2_tex;

    pvr_wait_ready();
    pvr_scene_begin();

    Vdp2DrawBackScreen();
    Vdp2DrawLineColorScreen();
}