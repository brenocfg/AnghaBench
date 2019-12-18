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
 scalar_t__ path_is_valid (char const*) ; 

__attribute__((used)) static const char *font_renderer_stb_get_default_font(void)
{
   static const char *paths[] = {
#if defined(_WIN32) && !defined(__WINRT__)
      "C:\\Windows\\Fonts\\consola.ttf",
      "C:\\Windows\\Fonts\\verdana.ttf",
#elif defined(__APPLE__)
      "/Library/Fonts/Microsoft/Candara.ttf",
      "/Library/Fonts/Verdana.ttf",
      "/Library/Fonts/Tahoma.ttf",
      "/Library/Fonts/Andale Mono.ttf",
      "/Library/Fonts/Courier New.ttf",
#elif defined(__ANDROID_API__)
      "/system/fonts/DroidSansMono.ttf",
      "/system/fonts/CutiveMono.ttf",
      "/system/fonts/DroidSans.ttf",
#elif defined(VITA)
      "vs0:data/external/font/pvf/c041056ts.ttf",
      "vs0:data/external/font/pvf/d013013ds.ttf",
      "vs0:data/external/font/pvf/e046323ms.ttf",
      "vs0:data/external/font/pvf/e046323ts.ttf",
      "vs0:data/external/font/pvf/k006004ds.ttf",
      "vs0:data/external/font/pvf/n023055ms.ttf",
      "vs0:data/external/font/pvf/n023055ts.ttf",
#elif !defined(__WINRT__)
      "/usr/share/fonts/TTF/DejaVuSansMono.ttf",
      "/usr/share/fonts/TTF/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono.ttf",
      "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "osd-font.ttf",
#endif
      NULL
   };

   const char **p;

   for (p = paths; *p; ++p)
      if (path_is_valid(*p))
         return *p;

   return NULL;
}