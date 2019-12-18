#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clearTexture; int updatedPalette; } ;
struct TYPE_4__ {int menuVisible; int clearVRAM; int fullscreen; TYPE_1__ iface; } ;
typedef  TYPE_2__ ps2_video_t ;

/* Variables and functions */

__attribute__((used)) static void ps2_set_texture_enable(void *data, bool enable, bool fullscreen)
{
   ps2_video_t *ps2 = (ps2_video_t*)data;
   if (ps2->menuVisible != enable) {
      /* If Menu change status, CLEAR VRAM */
      ps2->clearVRAM = true;
      ps2->iface.clearTexture = true;
      ps2->iface.updatedPalette = true;
   }
   ps2->menuVisible = enable;
   ps2->fullscreen = fullscreen;
}