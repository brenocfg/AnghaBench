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
struct TYPE_3__ {void* playlist_left_mode; void* playlist_right_mode; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 void* PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 scalar_t__ calloc (int,int) ; 

menu_thumbnail_path_data_t *menu_thumbnail_path_init(void)
{
   menu_thumbnail_path_data_t *path_data = (menu_thumbnail_path_data_t*)
      calloc(1, sizeof(*path_data));
   if (!path_data)
      return NULL;
   
   /* Set these manually, since the default enum
    * may not necessarily have a value of zero */
   path_data->playlist_right_mode = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   path_data->playlist_left_mode  = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   
   return path_data;
}