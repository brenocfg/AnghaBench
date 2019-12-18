#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_6__ {scalar_t__ status; scalar_t__ delay_timer; } ;
typedef  TYPE_1__ menu_thumbnail_t ;
typedef  int /*<<< orphan*/  menu_thumbnail_path_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 void* MENU_THUMBNAIL_STATUS_MISSING ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_UNKNOWN ; 
 float menu_animation_get_delta_time () ; 
 int /*<<< orphan*/  menu_thumbnail_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_thumbnail_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_playlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ menu_thumbnail_stream_delay ; 

void menu_thumbnail_process_streams(
      menu_thumbnail_path_data_t *path_data,
      playlist_t *playlist, size_t idx,
      menu_thumbnail_t *right_thumbnail, menu_thumbnail_t *left_thumbnail,
      bool on_screen)
{
   if (!right_thumbnail || !left_thumbnail)
      return;

   if (on_screen)
   {
      /* Entry is on-screen
       * > Only process if current status is
       *   MENU_THUMBNAIL_STATUS_UNKNOWN */
      bool process_right = (right_thumbnail->status == MENU_THUMBNAIL_STATUS_UNKNOWN);
      bool process_left  = (left_thumbnail->status  == MENU_THUMBNAIL_STATUS_UNKNOWN);

      if (process_right || process_left)
      {
         /* Check if stream delay timer has elapsed */
         float delta_time   = menu_animation_get_delta_time();
         bool request_right = false;
         bool request_left  = false;

         if (process_right)
         {
            right_thumbnail->delay_timer += delta_time;
            request_right                 =
                  (right_thumbnail->delay_timer > menu_thumbnail_stream_delay);
         }

         if (process_left)
         {
            left_thumbnail->delay_timer  += delta_time;
            request_left                  =
                  (left_thumbnail->delay_timer > menu_thumbnail_stream_delay);
         }

         /* Check if one or more thumbnails should be requested */
         if (request_right || request_left)
         {
            /* Sanity check */
            if (!path_data || !playlist)
               return;

            /* Update thumbnail content */
            if (!menu_thumbnail_set_content_playlist(path_data, playlist, idx))
            {
               /* Content is invalid
                * > Reset thumbnail and set missing status */
               if (request_right)
               {
                  menu_thumbnail_reset(right_thumbnail);
                  right_thumbnail->status = MENU_THUMBNAIL_STATUS_MISSING;
               }

               if (request_left)
               {
                  menu_thumbnail_reset(left_thumbnail);
                  left_thumbnail->status  = MENU_THUMBNAIL_STATUS_MISSING;
               }

               return;
            }

            /* Request image load */
            if (request_right)
               menu_thumbnail_request(
                     path_data, MENU_THUMBNAIL_RIGHT, playlist, idx, right_thumbnail);

            if (request_left)
               menu_thumbnail_request(
                     path_data, MENU_THUMBNAIL_LEFT, playlist, idx, left_thumbnail);
         }
      }
   }
   else
   {
      /* Entry is off-screen
       * > If status is MENU_THUMBNAIL_STATUS_UNKNOWN,
       *   thumbnail is already in a blank state - but we
       *   must ensure that delay timer is set to zero
       * > In all other cases, reset thumbnail */
      if (right_thumbnail->status == MENU_THUMBNAIL_STATUS_UNKNOWN)
         right_thumbnail->delay_timer = 0.0f;
      else
         menu_thumbnail_reset(right_thumbnail);

      if (left_thumbnail->status == MENU_THUMBNAIL_STATUS_UNKNOWN)
         left_thumbnail->delay_timer = 0.0f;
      else
         menu_thumbnail_reset(left_thumbnail);
   }
}