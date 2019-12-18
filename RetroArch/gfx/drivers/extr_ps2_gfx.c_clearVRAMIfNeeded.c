#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int updatedPalette; } ;
struct TYPE_5__ {int clearVRAM; int clearVRAM_font; TYPE_1__ iface; int /*<<< orphan*/  gsGlobal; int /*<<< orphan*/  PSM; int /*<<< orphan*/  coreTexture; } ;
typedef  TYPE_2__ ps2_video_t ;

/* Variables and functions */
 void const* RETRO_HW_FRAME_BUFFER_VALID ; 
 int /*<<< orphan*/  gsKit_vram_clear (int /*<<< orphan*/ ) ; 
 int texture_need_prepare (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clearVRAMIfNeeded(ps2_video_t *ps2, const void *frame, int width, int height)
{
   if (!ps2->clearVRAM) {
      if(frame && frame != RETRO_HW_FRAME_BUFFER_VALID) {
         bool coreVRAMClear = false;
         coreVRAMClear = texture_need_prepare(ps2->coreTexture, width, height, ps2->PSM);
         ps2->clearVRAM = ps2->clearVRAM || coreVRAMClear;
      }
   }

   if (ps2->clearVRAM) {
      gsKit_vram_clear(ps2->gsGlobal);
      ps2->iface.updatedPalette = true;
      ps2->clearVRAM_font = true; /* we need to upload also palette in the font driver */
   }
}