#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char const* stat_text; int /*<<< orphan*/  osd_stat_params; scalar_t__ statistics_show; } ;
typedef  TYPE_2__ video_frame_info_t ;
typedef  int uint64_t ;
struct retro_hw_ps2_insets {unsigned int right; } ;
struct font_params {int dummy; } ;
struct TYPE_13__ {int updatedPalette; int clearTexture; struct retro_hw_ps2_insets padding; } ;
struct TYPE_15__ {int /*<<< orphan*/  fullscreen; TYPE_4__* menuTexture; int /*<<< orphan*/  gsGlobal; scalar_t__ clearVRAM; scalar_t__ menuVisible; int /*<<< orphan*/  force_aspect; TYPE_4__* coreTexture; TYPE_1__ iface; int /*<<< orphan*/  core_filter; int /*<<< orphan*/  PSM; } ;
typedef  TYPE_3__ ps2_video_t ;
struct TYPE_16__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLACK ; 
 int /*<<< orphan*/  GS_PSM_CT32 ; 
 void const* RETRO_HW_FRAME_BUFFER_VALID ; 
 int /*<<< orphan*/  clearVRAMIfNeeded (TYPE_3__*,void const*,unsigned int,unsigned int) ; 
 struct retro_hw_ps2_insets empty_ps2_insets ; 
 int /*<<< orphan*/  font_driver_render_msg (TYPE_2__*,int /*<<< orphan*/ *,char const*,struct font_params const*) ; 
 int /*<<< orphan*/  gsKit_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsKit_texture_upload (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  prim_texture (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ,struct retro_hw_ps2_insets) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  ps2_texture_upload (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  refreshScreen (TYPE_3__*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  transfer_texture (TYPE_4__*,void const*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vram_alloc (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static bool ps2_gfx_frame(void *data, const void *frame,
      unsigned width, unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   ps2_video_t *ps2 = (ps2_video_t*)data;

   if (!width || !height)
      return false;

#if defined(DEBUG)
   if (frame_count%60==0) {
      printf("ps2_gfx_frame %lu\n", frame_count);
   }
#endif

   clearVRAMIfNeeded(ps2, frame, width, height);
   gsKit_clear(ps2->gsGlobal, GS_BLACK);

   if (frame) {
      bool sendPalette = false;
      struct retro_hw_ps2_insets padding = empty_ps2_insets;
      if (frame != RETRO_HW_FRAME_BUFFER_VALID){ /* Checking if the transfer is done in the core */
         /* calculate proper width based in the pitch */
         int bytes_per_pixel = (ps2->PSM == GS_PSM_CT32) ? 4 : 2;
         int real_width = pitch / bytes_per_pixel; 
         transfer_texture(ps2->coreTexture, frame, real_width, height, ps2->PSM, ps2->core_filter, 1);
         padding.right = real_width - width;
      } else {
         sendPalette = ps2->iface.updatedPalette;
         ps2->iface.updatedPalette = false;
         padding = ps2->iface.padding;
         if (ps2->iface.clearTexture) {
            ps2->iface.clearTexture = false;
         }
      }
      if(ps2->clearVRAM) {
         vram_alloc(ps2->gsGlobal, ps2->coreTexture);
      }
      ps2_texture_upload(ps2->gsGlobal, ps2->coreTexture, sendPalette);
      prim_texture(ps2->gsGlobal, ps2->coreTexture, 1, ps2->force_aspect, padding);
   }

   if (ps2->menuVisible) {
      bool texture_empty = !ps2->menuTexture->Width || !ps2->menuTexture->Height;
      if (!texture_empty) {
         if(ps2->clearVRAM) {
            vram_alloc(ps2->gsGlobal, ps2->menuTexture);
         }
         gsKit_texture_upload(ps2->gsGlobal, ps2->menuTexture);
         prim_texture(ps2->gsGlobal, ps2->menuTexture, 2, ps2->fullscreen, empty_ps2_insets);
      }
   } else if (video_info->statistics_show) {
      struct font_params *osd_params = (struct font_params*)
         &video_info->osd_stat_params;

      if (osd_params) {
         font_driver_render_msg(video_info, NULL, video_info->stat_text,
               (const struct font_params*)&video_info->osd_stat_params);
      }
   }

   if(!string_is_empty(msg)) {
      font_driver_render_msg(video_info, NULL, msg, NULL);
   }

   refreshScreen(ps2);

   return true;
}