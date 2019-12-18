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
struct TYPE_6__ {char* directory_autoconfig; char* directory_menu_config; char* path_menu_wallpaper; char* directory_assets; char* path_menu_xmb_font; char* directory_thumbnails; } ;
struct TYPE_5__ {char* input_joypad_driver; char* menu_driver; } ;
struct TYPE_7__ {TYPE_2__ paths; TYPE_1__ arrays; } ;
typedef  TYPE_3__ settings_t ;
typedef  enum application_special_type { ____Placeholder_application_special_type } application_special_type ;

/* Variables and functions */
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI 141 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT 140 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_ICONS 139 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_OZONE 138 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_SOUNDS 137 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB 136 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_BG 135 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_FONT 134 
#define  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_ICONS 133 
#define  APPLICATION_SPECIAL_DIRECTORY_AUTOCONFIG 132 
#define  APPLICATION_SPECIAL_DIRECTORY_CONFIG 131 
#define  APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_CHEEVOS_BADGES 130 
#define  APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_DISCORD_AVATARS 129 
#define  APPLICATION_SPECIAL_NONE 128 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,int) ; 
 int /*<<< orphan*/  fill_pathname_slash (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 char* xmb_theme_ident () ; 

void fill_pathname_application_special(char *s,
      size_t len, enum application_special_type type)
{
   switch (type)
   {
      case APPLICATION_SPECIAL_DIRECTORY_AUTOCONFIG:
         {
            settings_t *settings     = config_get_ptr();
            fill_pathname_join(s,
                  settings->paths.directory_autoconfig,
                  settings->arrays.input_joypad_driver,
                  len);
         }
         break;
      case APPLICATION_SPECIAL_DIRECTORY_CONFIG:
         {
            settings_t *settings     = config_get_ptr();

            /* Try config directory setting first,
             * fallback to the location of the current configuration file. */
            if (!string_is_empty(settings->paths.directory_menu_config))
               strlcpy(s, settings->paths.directory_menu_config, len);
            else if (!path_is_empty(RARCH_PATH_CONFIG))
               fill_pathname_basedir(s, path_get(RARCH_PATH_CONFIG), len);
         }
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_ICONS:
#ifdef HAVE_XMB
         {
            char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
            char *s2 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

            s1[0]    = '\0';
            s2[0]    = '\0';

            fill_pathname_application_special(s1,
                  PATH_MAX_LENGTH * sizeof(char),
                  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB);
            fill_pathname_join(s2, s1, "png",
                  PATH_MAX_LENGTH * sizeof(char)
                  );
            fill_pathname_slash(s2,
                  PATH_MAX_LENGTH * sizeof(char)
                  );
            strlcpy(s, s2, len);
            free(s1);
            free(s2);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_BG:
#ifdef HAVE_XMB
         {
            settings_t *settings     = config_get_ptr();

            if (!string_is_empty(settings->paths.path_menu_wallpaper))
               strlcpy(s, settings->paths.path_menu_wallpaper, len);
            else
            {
               char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

               s1[0] = '\0';

               fill_pathname_application_special(s1,
                     PATH_MAX_LENGTH * sizeof(char),
                     APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_ICONS);
               fill_pathname_join(s, s1, "bg.png", len);
               free(s1);
            }
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_SOUNDS:
         {
#ifdef HAVE_MENU
            settings_t *settings = config_get_ptr();
            const char *menu_ident = settings->arrays.menu_driver;
            char *s1 = (char*)calloc(1, PATH_MAX_LENGTH * sizeof(char));

            if (string_is_equal(menu_ident, "xmb"))
            {
               fill_pathname_application_special(s1, PATH_MAX_LENGTH * sizeof(char), APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB);

               if (!string_is_empty(s1))
                  strlcat(s1, "/sounds", PATH_MAX_LENGTH * sizeof(char));
            }
            else if (string_is_equal(menu_ident, "glui"))
            {
               fill_pathname_application_special(s1, PATH_MAX_LENGTH * sizeof(char), APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI);

               if (!string_is_empty(s1))
                  strlcat(s1, "/sounds", PATH_MAX_LENGTH * sizeof(char));
            }
            else if (string_is_equal(menu_ident, "ozone"))
            {
               fill_pathname_application_special(s1, PATH_MAX_LENGTH * sizeof(char), APPLICATION_SPECIAL_DIRECTORY_ASSETS_OZONE);

               if (!string_is_empty(s1))
                  strlcat(s1, "/sounds", PATH_MAX_LENGTH * sizeof(char));
            }

            if (string_is_empty(s1))
            {
               fill_pathname_join(
                     s1,
                     settings->paths.directory_assets,
                     "sounds",
                     PATH_MAX_LENGTH * sizeof(char)
               );
            }

            strlcpy(s, s1, len);
            free(s1);
#endif
         }

         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_OZONE:
#ifdef HAVE_OZONE
         {
            char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
            settings_t *settings     = config_get_ptr();

            s1[0] = '\0';

            fill_pathname_join(
                  s1,
                  settings->paths.directory_assets,
                  "ozone",
                  PATH_MAX_LENGTH * sizeof(char)
                  );
            strlcpy(s, s1, len);
            free(s1);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB:
#ifdef HAVE_XMB
         {
            char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
            settings_t *settings     = config_get_ptr();

            s1[0] = '\0';

            fill_pathname_join(
                  s1,
                  settings->paths.directory_assets,
                  "xmb",
                  PATH_MAX_LENGTH * sizeof(char)
                  );
            fill_pathname_join(s,
                  s1, xmb_theme_ident(), len);
            free(s1);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI:
#ifdef HAVE_MATERIALUI
         {
            settings_t *settings = config_get_ptr();

            fill_pathname_join(
                  s,
                  settings->paths.directory_assets,
                  "glui",
                  len);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_ICONS:
#ifdef HAVE_MATERIALUI
         {
            char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

            s1[0] = '\0';

            fill_pathname_application_special(s1,
                  PATH_MAX_LENGTH * sizeof(char),
                  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI);
            fill_pathname_slash(s1,
                  PATH_MAX_LENGTH * sizeof(char)
                  );
            strlcpy(s, s1, len);

            free(s1);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI_FONT:
#ifdef HAVE_MATERIALUI
         {
            char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

            s1[0] = '\0';

            fill_pathname_application_special(s1,
                  PATH_MAX_LENGTH * sizeof(char),
                  APPLICATION_SPECIAL_DIRECTORY_ASSETS_MATERIALUI);
            fill_pathname_join(s, s1, "font.ttf", len);

            free(s1);
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_FONT:
#ifdef HAVE_XMB
         {
            settings_t *settings = config_get_ptr();

            if (!string_is_empty(settings->paths.path_menu_xmb_font))
               strlcpy(s, settings->paths.path_menu_xmb_font, len);
            else
            {
               char *s1 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

               s1[0] = '\0';

               fill_pathname_application_special(s1,
                     PATH_MAX_LENGTH * sizeof(char),
                     APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB);
               fill_pathname_join(s, s1, "font.ttf", len);
               free(s1);
            }
         }
#endif
         break;
      case APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_DISCORD_AVATARS:
      {
        char *s1             = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
        char *s2             = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
        settings_t *settings = config_get_ptr();

        s1[0]                = '\0';
        s2[0]                = '\0';

        fill_pathname_join(s1,
              settings->paths.directory_thumbnails,
              "discord",
              len);
        fill_pathname_join(s2,
              s1, "avatars",
              PATH_MAX_LENGTH * sizeof(char)
              );
        fill_pathname_slash(s2,
              PATH_MAX_LENGTH * sizeof(char)
              );
        strlcpy(s, s2, len);
        free(s1);
        free(s2);
      }
      break;

      case APPLICATION_SPECIAL_DIRECTORY_THUMBNAILS_CHEEVOS_BADGES:
      {
        char *s1             = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
        char *s2             = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
        settings_t *settings = config_get_ptr();

        s1[0]                = '\0';
        s2[0]                = '\0';

        fill_pathname_join(s1,
              settings->paths.directory_thumbnails,
              "cheevos",
              len);
        fill_pathname_join(s2,
              s1, "badges",
              PATH_MAX_LENGTH * sizeof(char)
              );
        fill_pathname_slash(s2,
              PATH_MAX_LENGTH * sizeof(char)
              );
        strlcpy(s, s2, len);
        free(s1);
        free(s2);
      }
      break;

      case APPLICATION_SPECIAL_NONE:
      default:
         break;
   }
}