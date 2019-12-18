#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* right_path; char* left_path; char* content_path; char* content_label; char* content_core_name; char* content_db_name; char* content_img; void* playlist_left_mode; void* playlist_right_mode; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 void* PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/  fill_content_img (TYPE_1__*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

bool menu_thumbnail_set_content(menu_thumbnail_path_data_t *path_data, const char *label)
{
   if (!path_data)
      return false;
   
   /* When content is updated, must regenerate right/left
    * thumbnail paths */
   path_data->right_path[0]        = '\0';
   path_data->left_path[0]         = '\0';
   
   /* 'Reset' path_data content strings */
   path_data->content_path[0]      = '\0';
   path_data->content_label[0]     = '\0';
   path_data->content_core_name[0] = '\0';
   path_data->content_db_name[0]   = '\0';
   path_data->content_img[0]       = '\0';
   
   /* Must also reset playlist thumbnail display modes */
   path_data->playlist_right_mode  = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   path_data->playlist_left_mode   = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   
   if (string_is_empty(label))
      return false;
   
   /* Cache content label */
   strlcpy(path_data->content_label, label, sizeof(path_data->content_label));
   
   /* Determine content image name */
   fill_content_img(path_data);
   
   /* Have to set content path to *something*...
    * Just use label value (it doesn't matter) */
   strlcpy(path_data->content_path, label, sizeof(path_data->content_path));
   
   /* Redundant error check... */
   if (string_is_empty(path_data->content_img))
      return false;
   
   return true;
}