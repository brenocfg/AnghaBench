#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_system_av_info {int /*<<< orphan*/  geometry; } ;
struct retro_game_geometry {int base_width; int base_height; } ;
struct TYPE_5__ {int* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int retroarch_get_rotation () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,...) ; 
 struct retro_system_av_info* video_viewport_get_system_av_info () ; 

__attribute__((used)) static void setting_get_string_representation_uint_custom_viewport_width(rarch_setting_t *setting,
      char *s, size_t len)
{
   struct retro_game_geometry  *geom    = NULL;
   struct retro_system_av_info *av_info = NULL;
   if (!setting)
      return;

   av_info = video_viewport_get_system_av_info();
   geom    = (struct retro_game_geometry*)&av_info->geometry;

   if (!(retroarch_get_rotation() % 2) && (*setting->value.target.unsigned_integer%geom->base_width == 0))
      snprintf(s, len, "%u (%ux)",
            *setting->value.target.unsigned_integer,
            *setting->value.target.unsigned_integer / geom->base_width);
   else if ((retroarch_get_rotation() % 2) && (*setting->value.target.unsigned_integer%geom->base_height == 0))
      snprintf(s, len, "%u (%ux)",
            *setting->value.target.unsigned_integer,
            *setting->value.target.unsigned_integer / geom->base_height);
   else
      snprintf(s, len, "%u",
            *setting->value.target.unsigned_integer);
}