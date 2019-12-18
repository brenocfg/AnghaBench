#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_5__ {scalar_t__ status; scalar_t__ delay_timer; } ;
typedef  TYPE_1__ menu_thumbnail_t ;
typedef  int /*<<< orphan*/  menu_thumbnail_path_data_t ;
typedef  enum menu_thumbnail_id { ____Placeholder_menu_thumbnail_id } menu_thumbnail_id ;

/* Variables and functions */
 scalar_t__ MENU_THUMBNAIL_STATUS_MISSING ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_UNKNOWN ; 
 scalar_t__ menu_animation_get_delta_time () ; 
 int /*<<< orphan*/  menu_thumbnail_request (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_thumbnail_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_playlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ menu_thumbnail_stream_delay ; 

void menu_thumbnail_process_stream(
      menu_thumbnail_path_data_t *path_data, enum menu_thumbnail_id thumbnail_id,
      playlist_t *playlist, size_t idx, menu_thumbnail_t *thumbnail, bool on_screen)
{
   if (!thumbnail)
      return;

   if (on_screen)
   {
      /* Entry is on-screen
       * > Only process if current status is
       *   MENU_THUMBNAIL_STATUS_UNKNOWN */
      if (thumbnail->status == MENU_THUMBNAIL_STATUS_UNKNOWN)
      {
         /* Check if stream delay timer has elapsed */
         thumbnail->delay_timer += menu_animation_get_delta_time();

         if (thumbnail->delay_timer > menu_thumbnail_stream_delay)
         {
            /* Sanity check */
            if (!path_data || !playlist)
               return;

            /* Update thumbnail content */
            if (!menu_thumbnail_set_content_playlist(path_data, playlist, idx))
            {
               /* Content is invalid
                * > Reset thumbnail and set missing status */
               menu_thumbnail_reset(thumbnail);
               thumbnail->status = MENU_THUMBNAIL_STATUS_MISSING;
               return;
            }

            /* Request image load */
            menu_thumbnail_request(
                  path_data, thumbnail_id, playlist, idx, thumbnail);
         }
      }
   }
   else
   {
      /* Entry is off-screen
       * > If status is MENU_THUMBNAIL_STATUS_UNKNOWN,
       *   thumbnail is already in a blank state - but we
       *   must ensure that delay timer is set to zero */
      if (thumbnail->status == MENU_THUMBNAIL_STATUS_UNKNOWN)
         thumbnail->delay_timer = 0.0f;
      /* In all other cases, reset thumbnail */
      else
         menu_thumbnail_reset(thumbnail);
   }
}