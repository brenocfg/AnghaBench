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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int vblank_not_reached; } ;
typedef  TYPE_1__ psp1_video_t ;

/* Variables and functions */

__attribute__((used)) static void psp_on_vblank(u32 sub, psp1_video_t *psp)
{
   if (psp)
      psp->vblank_not_reached = false;
}