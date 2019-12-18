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
struct TYPE_3__ {char* content_path; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 scalar_t__ string_is_empty (char*) ; 

bool menu_thumbnail_get_content_path(
      menu_thumbnail_path_data_t *path_data, const char **content_path)
{
   if (!path_data)
      return false;
   
   if (!content_path)
      return false;
   
   if (string_is_empty(path_data->content_path))
      return false;
   
   *content_path = path_data->content_path;
   
   return true;
}