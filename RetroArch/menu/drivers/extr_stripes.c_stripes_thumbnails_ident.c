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
struct TYPE_4__ {char menu_thumbnails; char menu_left_thumbnails; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_OFF ; 
 TYPE_2__* config_get_ptr () ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *stripes_thumbnails_ident(char pos)
{
   char folder          = 0;
   settings_t *settings = config_get_ptr();

   if (pos == 'R')
      folder = settings->uints.menu_thumbnails;
   if (pos == 'L')
      folder = settings->uints.menu_left_thumbnails;

   switch (folder)
   {
      case 1:
         return "Named_Snaps";
      case 2:
         return "Named_Titles";
      case 3:
         return "Named_Boxarts";
      case 0:
      default:
         break;
   }

   return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF);
}