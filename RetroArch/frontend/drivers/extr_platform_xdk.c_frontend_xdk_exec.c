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
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  game_path ;
struct TYPE_4__ {scalar_t__ Data; } ;
typedef  TYPE_1__ LAUNCH_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LAUNCH_DATA_SIZE ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  XLaunchNewImage (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  XSetLaunchData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  verbosity_disable () ; 
 int /*<<< orphan*/  verbosity_enable () ; 
 int verbosity_is_enabled () ; 

__attribute__((used)) static void frontend_xdk_exec(const char *path, bool should_load_game)
{
#ifndef IS_SALAMANDER
   bool original_verbose       = verbosity_is_enabled();
#endif
#if defined(_XBOX1)
   LAUNCH_DATA ptr;
#elif defined(_XBOX360)
   char game_path[1024]        = {0};
#endif
   (void)should_load_game;

#ifdef IS_SALAMANDER
   if (!string_is_empty(path))
      XLaunchNewImage(path, NULL);
#else
#if defined(_XBOX1)
   memset(&ptr, 0, sizeof(ptr));

   if (should_load_game && !path_is_empty(RARCH_PATH_CONTENT))
      snprintf((char*)ptr.Data, sizeof(ptr.Data), "%s", path_get(RARCH_PATH_CONTENT));

   if (!string_is_empty(path))
      XLaunchNewImage(path, !string_is_empty((const char*)ptr.Data) ? &ptr : NULL);
#elif defined(_XBOX360)
   if (should_load_game && !path_is_empty(RARCH_PATH_CONTENT))
   {
      strlcpy(game_path, path_get(RARCH_PATH_CONTENT), sizeof(game_path));
      XSetLaunchData(game_path, MAX_LAUNCH_DATA_SIZE);
   }

   if (!string_is_empty(path))
      XLaunchNewImage(path, 0);
#endif
#endif
#ifndef IS_SALAMANDER
   if (original_verbose)
      verbosity_enable();
   else
      verbosity_disable();
#endif
}