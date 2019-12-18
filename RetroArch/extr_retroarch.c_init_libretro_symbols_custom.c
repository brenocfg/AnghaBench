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
struct retro_core_t {int dummy; } ;
typedef  enum rarch_core_type { ____Placeholder_rarch_core_type } rarch_core_type ;
typedef  int /*<<< orphan*/  dylib_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_SYMBOLS (int /*<<< orphan*/ ) ; 
#define  CORE_TYPE_DUMMY 135 
#define  CORE_TYPE_FFMPEG 134 
#define  CORE_TYPE_GONG 133 
#define  CORE_TYPE_IMAGEVIEWER 132 
#define  CORE_TYPE_MPV 131 
#define  CORE_TYPE_NETRETROPAD 130 
#define  CORE_TYPE_PLAIN 129 
#define  CORE_TYPE_VIDEO_PROCESSOR 128 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_FAILED_TO_OPEN_LIBRETRO_CORE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  SYMBOL ; 
 int /*<<< orphan*/  SYMBOL_DUMMY ; 
 int /*<<< orphan*/  SYMBOL_FFMPEG ; 
 int /*<<< orphan*/  SYMBOL_GONG ; 
 int /*<<< orphan*/  SYMBOL_IMAGEVIEWER ; 
 int /*<<< orphan*/  SYMBOL_MPV ; 
 int /*<<< orphan*/  SYMBOL_NETRETROPAD ; 
 int /*<<< orphan*/  SYMBOL_VIDEOPROCESSOR ; 
 int /*<<< orphan*/  dylib_error () ; 
 int /*<<< orphan*/  dylib_load (char const*) ; 
 int /*<<< orphan*/  lib_handle ; 
 int /*<<< orphan*/  load_dynamic_core (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get_realsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  retroarch_fail (int,char*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static bool init_libretro_symbols_custom(enum rarch_core_type type,
      struct retro_core_t *current_core, const char *lib_path, void *_lib_handle_p)
{
#ifdef HAVE_DYNAMIC
   /* the library handle for use with the SYMBOL macro */
   dylib_t lib_handle_local;
#endif

   switch (type)
   {
      case CORE_TYPE_PLAIN:
         {
#ifdef HAVE_DYNAMIC
#ifdef HAVE_RUNAHEAD
            dylib_t *lib_handle_p = (dylib_t*)_lib_handle_p;
            if (!lib_path || !lib_handle_p)
#endif
            {
               const char *path = path_get(RARCH_PATH_CORE);

               if (string_is_empty(path))
               {
                  RARCH_ERR("Frontend is built for dynamic libretro cores, but "
                        "path is not set. Cannot continue.\n");
                  retroarch_fail(1, "init_libretro_symbols()");
               }

               RARCH_LOG("Loading dynamic libretro core from: \"%s\"\n",
                     path);

               if (!load_dynamic_core(
                        path,
                        path_get_ptr(RARCH_PATH_CORE),
                        path_get_realsize(RARCH_PATH_CORE)
                        ))
               {
                  RARCH_ERR("Failed to open libretro core: \"%s\"\nError(s): %s\n", path, dylib_error());
                  runloop_msg_queue_push(msg_hash_to_str(MSG_FAILED_TO_OPEN_LIBRETRO_CORE),
                        1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
                  return false;
               }
               lib_handle_local = lib_handle;
            }
#ifdef HAVE_RUNAHEAD
            else
            {
               /* for a secondary core, we already have a
                * primary library loaded, so we can skip
                * some checks and just load the library */
               retro_assert(lib_path != NULL && lib_handle_p != NULL);
               lib_handle_local = dylib_load(lib_path);

               if (!lib_handle_local)
                  return false;
               *lib_handle_p = lib_handle_local;
            }
#endif
#endif

            CORE_SYMBOLS(SYMBOL);
         }
         break;
      case CORE_TYPE_DUMMY:
         CORE_SYMBOLS(SYMBOL_DUMMY);
         break;
      case CORE_TYPE_FFMPEG:
#ifdef HAVE_FFMPEG
         CORE_SYMBOLS(SYMBOL_FFMPEG);
#endif
         break;
      case CORE_TYPE_MPV:
#ifdef HAVE_MPV
         CORE_SYMBOLS(SYMBOL_MPV);
#endif
         break;
      case CORE_TYPE_IMAGEVIEWER:
#ifdef HAVE_IMAGEVIEWER
         CORE_SYMBOLS(SYMBOL_IMAGEVIEWER);
#endif
         break;
      case CORE_TYPE_NETRETROPAD:
#if defined(HAVE_NETWORKING) && defined(HAVE_NETWORKGAMEPAD)
         CORE_SYMBOLS(SYMBOL_NETRETROPAD);
#endif
         break;
      case CORE_TYPE_VIDEO_PROCESSOR:
#if defined(HAVE_VIDEOPROCESSOR)
         CORE_SYMBOLS(SYMBOL_VIDEOPROCESSOR);
#endif
         break;
      case CORE_TYPE_GONG:
#ifdef HAVE_EASTEREGG
         CORE_SYMBOLS(SYMBOL_GONG);
#endif
         break;
   }

   return true;
}