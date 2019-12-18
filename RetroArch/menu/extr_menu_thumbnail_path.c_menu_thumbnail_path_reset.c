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
struct TYPE_3__ {char* system; char* content_path; char* content_label; char* content_core_name; char* content_db_name; char* content_img; char* right_path; char* left_path; void* playlist_left_mode; void* playlist_right_mode; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 void* PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 

void menu_thumbnail_path_reset(menu_thumbnail_path_data_t *path_data)
{
   if (!path_data)
      return;
   
   path_data->system[0]            = '\0';
   path_data->content_path[0]      = '\0';
   path_data->content_label[0]     = '\0';
   path_data->content_core_name[0] = '\0';
   path_data->content_db_name[0]   = '\0';
   path_data->content_img[0]       = '\0';
   path_data->right_path[0]        = '\0';
   path_data->left_path[0]         = '\0';
   
   path_data->playlist_right_mode = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   path_data->playlist_left_mode  = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
}