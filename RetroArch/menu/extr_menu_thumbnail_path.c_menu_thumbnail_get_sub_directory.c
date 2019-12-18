#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

bool menu_thumbnail_get_sub_directory(unsigned type_idx, const char **sub_directory)
{
   if (!sub_directory)
      return false;
   
   switch (type_idx)
   {
      case 1:
         *sub_directory = "Named_Snaps";
         return true;
      case 2:
         *sub_directory = "Named_Titles";
         return true;
      case 3:
         *sub_directory = "Named_Boxarts";
         return true;
      case 0:
      default:
         break;
   }
   
   return false;
}