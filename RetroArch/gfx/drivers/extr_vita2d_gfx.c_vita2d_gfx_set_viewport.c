#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {unsigned int width; unsigned int height; int x; int y; float minDepth; float maxDepth; } ;
struct TYPE_11__ {TYPE_7__ vp; scalar_t__ keep_aspect; } ;
typedef  TYPE_3__ vita_video_t ;
struct video_viewport {int x; int y; unsigned int width; unsigned int height; } ;
struct video_ortho {int member_1; int member_2; int member_4; int member_5; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_9__ {scalar_t__ video_scale_integer; } ;
struct TYPE_12__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_13__ {float* aspect; unsigned int width; unsigned int height; } ;
typedef  TYPE_5__ gfx_ctx_aspect_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int) ; 
 TYPE_4__* config_get_ptr () ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 float video_driver_get_aspect_ratio () ; 
 struct video_viewport* video_viewport_get_custom () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_7__*,unsigned int,unsigned int,float,scalar_t__) ; 
 int /*<<< orphan*/  vita2d_set_projection (TYPE_3__*,struct video_ortho*,int) ; 

__attribute__((used)) static void vita2d_gfx_set_viewport(void *data, unsigned viewport_width,
      unsigned viewport_height, bool force_full, bool allow_rotate)
{
   gfx_ctx_aspect_t aspect_data;
   int x                    = 0;
   int y                    = 0;
   float device_aspect      = (float)viewport_width / viewport_height;
   struct video_ortho ortho = {0, 1, 1, 0, -1, 1};
   settings_t *settings     = config_get_ptr();
   vita_video_t *vita       = (vita_video_t*)data;

   aspect_data.aspect       = &device_aspect;
   aspect_data.width        = viewport_width;
   aspect_data.height       = viewport_height;

   if (settings->bools.video_scale_integer && !force_full)
   {
      video_viewport_get_scaled_integer(&vita->vp,
            viewport_width, viewport_height,
            video_driver_get_aspect_ratio(), vita->keep_aspect);
      viewport_width  = vita->vp.width;
      viewport_height = vita->vp.height;
   }
   else if (vita->keep_aspect && !force_full)
   {
      float desired_aspect = video_driver_get_aspect_ratio();

#if defined(HAVE_MENU)
      if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         const struct video_viewport *custom = video_viewport_get_custom();

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

      vita->vp.x      = x;
      vita->vp.y      = y;
      vita->vp.width  = viewport_width;
      vita->vp.height = viewport_height;
   }
   else
   {
      vita->vp.x      = 0;
      vita->vp.y      = 0;
      vita->vp.width  = viewport_width;
      vita->vp.height = viewport_height;
   }

   vita2d_set_projection(vita, &ortho, allow_rotate);

   /* Set last backbuffer viewport. */
   if (!force_full)
   {
      vita->vp.width  = viewport_width;
      vita->vp.height = viewport_height;
   }

#if 0
   vita->vp.x          = (float)vita->vp.x;
   vita->vp.y          = (float)vita->vp.y;
   vita->vp.width      = (float)vita->vp.width;
   vita->vp.height     = (float)vita->vp.height;
   vita->vp.minDepth   = 0.0f;
   vita->vp.maxDepth   = 1.0f;

   RARCH_LOG("Setting viewport @ %ux%u\n", viewport_width, viewport_height);
#endif
}