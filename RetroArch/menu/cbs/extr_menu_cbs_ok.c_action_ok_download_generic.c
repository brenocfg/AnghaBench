#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct string_list {TYPE_1__* elems; } ;
struct TYPE_8__ {char* network_buildbot_assets_url; char const* network_buildbot_url; } ;
struct TYPE_9__ {TYPE_2__ paths; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  s3 ;
typedef  int /*<<< orphan*/  s2 ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;
struct TYPE_10__ {int enum_idx; char* path; } ;
typedef  TYPE_4__ file_transfer_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
struct TYPE_7__ {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_LAKKA_URL ; 
#define  MENU_ENUM_LABEL_CB_CORE_CONTENT_DOWNLOAD 140 
#define  MENU_ENUM_LABEL_CB_CORE_THUMBNAILS_DOWNLOAD 139 
#define  MENU_ENUM_LABEL_CB_DOWNLOAD_URL 138 
#define  MENU_ENUM_LABEL_CB_LAKKA_DOWNLOAD 137 
#define  MENU_ENUM_LABEL_CB_UPDATE_ASSETS 136 
#define  MENU_ENUM_LABEL_CB_UPDATE_AUTOCONFIG_PROFILES 135 
#define  MENU_ENUM_LABEL_CB_UPDATE_CHEATS 134 
#define  MENU_ENUM_LABEL_CB_UPDATE_CORE_INFO_FILES 133 
#define  MENU_ENUM_LABEL_CB_UPDATE_DATABASES 132 
#define  MENU_ENUM_LABEL_CB_UPDATE_OVERLAYS 131 
#define  MENU_ENUM_LABEL_CB_UPDATE_SHADERS_CG 130 
#define  MENU_ENUM_LABEL_CB_UPDATE_SHADERS_GLSL 129 
#define  MENU_ENUM_LABEL_CB_UPDATE_SHADERS_SLANG 128 
 int PATH_MAX_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cb_generic_dir_download ; 
 int /*<<< orphan*/  cb_generic_download ; 
 TYPE_3__* config_get_ptr () ; 
 char* file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char const*,int) ; 
 char const* lakka_get_project () ; 
 int /*<<< orphan*/  msg_hash_to_str (int) ; 
 int /*<<< orphan*/  net_http_urlencode_full (char*,char*,int) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_push_http_transfer (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int action_ok_download_generic(const char *path,
      const char *label, const char *menu_label,
      unsigned type, size_t idx, size_t entry_idx,
      enum msg_hash_enums enum_idx)
{
#ifdef HAVE_NETWORKING
   char s[PATH_MAX_LENGTH];
   char s2[PATH_MAX_LENGTH];
   char s3[PATH_MAX_LENGTH];
   file_transfer_t *transf = NULL;
   settings_t *settings         = config_get_ptr();
   bool suppress_msg            = false;
   retro_task_callback_t cb     = cb_generic_download;

   s[0] = s2[0] = s3[0] = '\0';

   fill_pathname_join(s,
         settings->paths.network_buildbot_assets_url,
         "frontend", sizeof(s));

   switch (enum_idx)
   {
      case MENU_ENUM_LABEL_CB_DOWNLOAD_URL:
         suppress_msg = true;
         fill_pathname_join(s, label,
               path, sizeof(s));
         path = s;
         cb = cb_generic_dir_download;
         break;
      case MENU_ENUM_LABEL_CB_CORE_CONTENT_DOWNLOAD:
         {
            struct string_list *str_list = string_split(menu_label, ";");
            strlcpy(s, str_list->elems[0].data, sizeof(s));
            string_list_free(str_list);
         }
         break;
      case MENU_ENUM_LABEL_CB_LAKKA_DOWNLOAD:
#ifdef HAVE_LAKKA
         /* TODO unhardcode this path*/
         fill_pathname_join(s, file_path_str(FILE_PATH_LAKKA_URL),
               lakka_get_project(), sizeof(s));
#endif
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_ASSETS:
         path = "assets.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_AUTOCONFIG_PROFILES:
         path = "autoconfig.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_CORE_INFO_FILES:
         path = "info.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_CHEATS:
         path = "cheats.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_OVERLAYS:
         path = "overlays.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_DATABASES:
         path = "database-rdb.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_SHADERS_GLSL:
         path = "shaders_glsl.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_SHADERS_SLANG:
         path = "shaders_slang.zip";
         break;
      case MENU_ENUM_LABEL_CB_UPDATE_SHADERS_CG:
         path = "shaders_cg.zip";
         break;
      case MENU_ENUM_LABEL_CB_CORE_THUMBNAILS_DOWNLOAD:
         strlcpy(s, "http://thumbnailpacks.libretro.com", sizeof(s));
         break;
      default:
         strlcpy(s, settings->paths.network_buildbot_url, sizeof(s));
         break;
   }

   fill_pathname_join(s2, s, path, sizeof(s2));

   transf           = (file_transfer_t*)calloc(1, sizeof(*transf));
   transf->enum_idx = enum_idx;
   strlcpy(transf->path, path, sizeof(transf->path));

   if (string_is_equal(path, s))
      net_http_urlencode_full(s3, s, sizeof(s3));
   else
      net_http_urlencode_full(s3, s2, sizeof(s3));

   task_push_http_transfer(s3, suppress_msg, msg_hash_to_str(enum_idx), cb, transf);
#endif
   return 0;
}