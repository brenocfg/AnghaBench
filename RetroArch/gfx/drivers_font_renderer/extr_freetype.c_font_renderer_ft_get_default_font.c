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
struct TYPE_4__ {int /*<<< orphan*/  directory_assets; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int PATH_MAX_LENGTH ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char*,int) ; 
 char const** font_paths ; 
 scalar_t__ path_is_valid (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static const char *font_renderer_ft_get_default_font(void)
{
#ifdef WIIU
   return "";
#else
   size_t i;
#if 0
   char asset_path[PATH_MAX_LENGTH];
#endif

   for (i = 0; i < ARRAY_SIZE(font_paths); i++)
   {
#if 0
      /* Check if we are getting the font from the assets directory. */
      if (string_is_equal(font_paths[i], "assets://pkg/osd-font.ttf"))
      {
         settings_t *settings = config_get_ptr();
         fill_pathname_join(asset_path,
               settings->paths.directory_assets, "pkg/osd-font.ttf", PATH_MAX_LENGTH);
         font_paths[i] = asset_path;
      }
#endif

      if (path_is_valid(font_paths[i]))
         return font_paths[i];
   }

   return NULL;
#endif
}