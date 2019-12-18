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
struct TYPE_3__ {char* right_path; char* left_path; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;
typedef  enum menu_thumbnail_id { ____Placeholder_menu_thumbnail_id } menu_thumbnail_id ;

/* Variables and functions */
#define  MENU_THUMBNAIL_LEFT 129 
#define  MENU_THUMBNAIL_RIGHT 128 
 scalar_t__ string_is_empty (char*) ; 

bool menu_thumbnail_get_path(
      menu_thumbnail_path_data_t *path_data,
      enum menu_thumbnail_id thumbnail_id, const char **path)
{
   char *thumbnail_path = NULL;
   
   if (!path_data)
      return false;
   
   if (!path)
      return false;
   
   switch (thumbnail_id)
   {
      case MENU_THUMBNAIL_RIGHT:
         thumbnail_path = path_data->right_path;
         break;
      case MENU_THUMBNAIL_LEFT:
         thumbnail_path = path_data->left_path;
         break;
      default:
         return false;
   }
   
   if (string_is_empty(thumbnail_path))
      return false;
   
   *path = thumbnail_path;
   
   return true;
}