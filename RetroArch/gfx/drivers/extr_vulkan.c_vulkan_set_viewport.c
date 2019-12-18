#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_14__ {float x; float y; float width; float height; float minDepth; float maxDepth; } ;
struct TYPE_19__ {unsigned int width; unsigned int height; int x; int y; } ;
struct TYPE_16__ {unsigned int video_width; unsigned int video_height; unsigned int vp_out_width; unsigned int vp_out_height; TYPE_4__ tracker; TYPE_3__ vk_vp; TYPE_9__ vp; scalar_t__ keep_aspect; } ;
typedef  TYPE_5__ vk_t ;
struct video_viewport {int x; int y; unsigned int width; unsigned int height; } ;
struct video_ortho {int member_1; int member_3; int member_4; int member_5; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_12__ {scalar_t__ video_scale_integer; } ;
struct TYPE_17__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_6__ settings_t ;
struct TYPE_18__ {float* aspect; unsigned int width; unsigned int height; } ;
typedef  TYPE_7__ gfx_ctx_aspect_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VULKAN_DIRTY_DYNAMIC_BIT ; 
 TYPE_6__* config_get_ptr () ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 int /*<<< orphan*/  video_context_driver_translate_aspect (TYPE_7__*) ; 
 float video_driver_get_aspect_ratio () ; 
 struct video_viewport* video_viewport_get_custom () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_9__*,unsigned int,unsigned int,float,scalar_t__) ; 
 int /*<<< orphan*/  vulkan_set_projection (TYPE_5__*,struct video_ortho*,int) ; 

__attribute__((used)) static void vulkan_set_viewport(void *data, unsigned viewport_width,
      unsigned viewport_height, bool force_full, bool allow_rotate)
{
   gfx_ctx_aspect_t aspect_data;
   int x                  = 0;
   int y                  = 0;
   float device_aspect    = (float)viewport_width / viewport_height;
   struct video_ortho ortho = {0, 1, 0, 1, -1, 1};
   settings_t *settings   = config_get_ptr();
   vk_t *vk               = (vk_t*)data;
   unsigned width         = vk->video_width;
   unsigned height        = vk->video_height;

   aspect_data.aspect     = &device_aspect;
   aspect_data.width      = viewport_width;
   aspect_data.height     = viewport_height;

   video_context_driver_translate_aspect(&aspect_data);

   if (settings->bools.video_scale_integer && !force_full)
   {
      video_viewport_get_scaled_integer(&vk->vp,
            viewport_width, viewport_height,
            video_driver_get_aspect_ratio(), vk->keep_aspect);
      viewport_width  = vk->vp.width;
      viewport_height = vk->vp.height;
   }
   else if (vk->keep_aspect && !force_full)
   {
      float desired_aspect = video_driver_get_aspect_ratio();

#if defined(HAVE_MENU)
      if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         const struct video_viewport *custom = video_viewport_get_custom();

         /* Vulkan has top-left origin viewport. */
         x               = custom->x;
         y               = custom->y;
         viewport_width  = custom->width;
         viewport_height = custom->height;
      }
      else
#endif
      {
         float delta;

         if (fabsf(device_aspect - desired_aspect) < 0.0001f)
         {
            /* If the aspect ratios of screen and desired aspect
             * ratio are sufficiently equal (floating point stuff),
             * assume they are actually equal.
             */
         }
         else if (device_aspect > desired_aspect)
         {
            delta          = (desired_aspect / device_aspect - 1.0f)
               / 2.0f + 0.5f;
            x              = (int)roundf(viewport_width * (0.5f - delta));
            viewport_width = (unsigned)roundf(2.0f * viewport_width * delta);
         }
         else
         {
            delta           = (device_aspect / desired_aspect - 1.0f)
               / 2.0f + 0.5f;
            y               = (int)roundf(viewport_height * (0.5f - delta));
            viewport_height = (unsigned)roundf(2.0f * viewport_height * delta);
         }
      }

      vk->vp.x      = x;
      vk->vp.y      = y;
      vk->vp.width  = viewport_width;
      vk->vp.height = viewport_height;
   }
   else
   {
      vk->vp.x      = 0;
      vk->vp.y      = 0;
      vk->vp.width  = viewport_width;
      vk->vp.height = viewport_height;
   }

#if defined(RARCH_MOBILE)
   /* In portrait mode, we want viewport to gravitate to top of screen. */
   if (device_aspect < 1.0f)
      vk->vp.y = 0;
#endif

   vulkan_set_projection(vk, &ortho, allow_rotate);

   /* Set last backbuffer viewport. */
   if (!force_full)
   {
      vk->vp_out_width  = viewport_width;
      vk->vp_out_height = viewport_height;
   }

   vk->vk_vp.x          = (float)vk->vp.x;
   vk->vk_vp.y          = (float)vk->vp.y;
   vk->vk_vp.width      = (float)vk->vp.width;
   vk->vk_vp.height     = (float)vk->vp.height;
   vk->vk_vp.minDepth   = 0.0f;
   vk->vk_vp.maxDepth   = 1.0f;

   vk->tracker.dirty |= VULKAN_DIRTY_DYNAMIC_BIT;

#if 0
   RARCH_LOG("Setting viewport @ %ux%u\n", viewport_width, viewport_height);
#endif
}