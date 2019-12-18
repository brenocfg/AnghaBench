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
struct texture_image {scalar_t__ list_id; int width; int height; TYPE_2__* thumbnail; } ;
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  struct texture_image menu_thumbnail_tag_t ;
struct TYPE_4__ {uintptr_t tag; float target_value; float* subject; int /*<<< orphan*/ * userdata; int /*<<< orphan*/ * cb; int /*<<< orphan*/  duration; int /*<<< orphan*/  easing_enum; } ;
typedef  TYPE_1__ menu_animation_ctx_entry_t ;
struct TYPE_5__ {scalar_t__ status; int width; int height; float alpha; scalar_t__ texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_AVAILABLE ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_MISSING ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_PENDING ; 
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  free (struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_thumbnail_fade_duration ; 
 scalar_t__ menu_thumbnail_list_id ; 
 int /*<<< orphan*/  menu_thumbnail_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  video_driver_texture_load (struct texture_image*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void menu_thumbnail_handle_upload(
      retro_task_t *task, void *task_data, void *user_data, const char *err)
{
   struct texture_image *img           = (struct texture_image*)task_data;
   menu_thumbnail_tag_t *thumbnail_tag = (menu_thumbnail_tag_t*)user_data;
   menu_animation_ctx_entry_t animation_entry;

   /* Sanity check */
   if (!thumbnail_tag)
      goto end;

   /* Ensure that we are operating on the correct
    * thumbnail... */
   if (thumbnail_tag->list_id != menu_thumbnail_list_id)
      goto end;

   /* Only process image if we are waiting for it */
   if (thumbnail_tag->thumbnail->status != MENU_THUMBNAIL_STATUS_PENDING)
      goto end;

   /* Sanity check: if thumbnail already has a texture,
    * we're in some kind of weird error state - in this
    * case, the best course of action is to just reset
    * the thumbnail... */
   if (thumbnail_tag->thumbnail->texture)
      menu_thumbnail_reset(thumbnail_tag->thumbnail);

   /* Set thumbnail 'missing' status by default
    * (saves a number of checks later) */
   thumbnail_tag->thumbnail->status = MENU_THUMBNAIL_STATUS_MISSING;

   /* Check we have a valid image */
   if (!img)
      goto end;

   if ((img->width < 1) || (img->height < 1))
      goto end;

   /* Upload texture to GPU */
   if (!video_driver_texture_load(
            img, TEXTURE_FILTER_MIPMAP_LINEAR, &thumbnail_tag->thumbnail->texture))
      goto end;

   /* Cache dimensions */
   thumbnail_tag->thumbnail->width  = img->width;
   thumbnail_tag->thumbnail->height = img->height;

   /* Update thumbnail status */
   thumbnail_tag->thumbnail->status = MENU_THUMBNAIL_STATUS_AVAILABLE;

   /* Trigger 'fade in' animation */
   thumbnail_tag->thumbnail->alpha  = 0.0f;

   animation_entry.easing_enum      = EASING_OUT_QUAD;
   animation_entry.tag              = (uintptr_t)&thumbnail_tag->thumbnail->alpha;
   animation_entry.duration         = menu_thumbnail_fade_duration;
   animation_entry.target_value     = 1.0f;
   animation_entry.subject          = &thumbnail_tag->thumbnail->alpha;
   animation_entry.cb               = NULL;
   animation_entry.userdata         = NULL;

   menu_animation_push(&animation_entry);

end:
   /* Clean up */
   if (img)
   {
      image_texture_free(img);
      free(img);
   }

   if (thumbnail_tag)
      free(thumbnail_tag);
}