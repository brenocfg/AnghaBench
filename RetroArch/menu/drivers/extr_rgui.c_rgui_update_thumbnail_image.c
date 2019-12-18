#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ menu_rgui_inline_thumbnails; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_10__ {int show_fs_thumbnail; } ;
typedef  TYPE_3__ rgui_t ;
struct TYPE_12__ {int is_valid; char* path; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_11__ {int is_valid; char* path; scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 TYPE_6__ fs_thumbnail ; 
 TYPE_5__ mini_thumbnail ; 
 int /*<<< orphan*/  rgui_scan_selected_entry_thumbnail (TYPE_3__*,int) ; 

__attribute__((used)) static void rgui_update_thumbnail_image(void *userdata)
{
   rgui_t *rgui         = (rgui_t*)userdata;
   settings_t *settings = config_get_ptr();
   if (!rgui || !settings)
      return;

   rgui->show_fs_thumbnail = !rgui->show_fs_thumbnail;

   /* It is possible that we are waiting for a 'right' thumbnail
    * image to load at this point. If so, and we are displaying
    * inline thumbnails, then 'fs_thumbnail' and 'mini_thumbnail'
    * can get mixed up. To avoid this, we simply 'reset' the
    * currently inactive right thumbnail. */
   if (settings->bools.menu_rgui_inline_thumbnails)
   {
      if (rgui->show_fs_thumbnail)
      {
         mini_thumbnail.width = 0;
         mini_thumbnail.height = 0;
         mini_thumbnail.is_valid = false;
         mini_thumbnail.path[0] = '\0';
      }
      else
      {
         fs_thumbnail.width = 0;
         fs_thumbnail.height = 0;
         fs_thumbnail.is_valid = false;
         fs_thumbnail.path[0] = '\0';
      }
   }

   /* Note that we always load thumbnails immediately
    * when toggling via the 'scan' button (scheduling a
    * delayed load here would make for a poor user
    * experience...) */
   rgui_scan_selected_entry_thumbnail(rgui, true);
}