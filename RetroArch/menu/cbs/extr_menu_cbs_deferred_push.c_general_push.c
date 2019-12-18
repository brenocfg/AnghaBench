#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  tmp_str2 ;
typedef  int /*<<< orphan*/  tmp_str ;
struct string_list {unsigned int size; TYPE_1__* elems; } ;
struct retro_system_info {char* valid_extensions; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ multimedia_builtin_imageviewer_enable; scalar_t__ multimedia_builtin_mediaplayer_enable; int /*<<< orphan*/  filter_by_current_core; } ;
struct TYPE_14__ {TYPE_2__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_15__ {int /*<<< orphan*/  scratch_buf; int /*<<< orphan*/  scratch2_buf; } ;
typedef  TYPE_4__ menu_handle_t ;
struct TYPE_16__ {char* path; char* label; char* exts; int /*<<< orphan*/  setting; int /*<<< orphan*/  enum_idx; int /*<<< orphan*/  type_default; } ;
typedef  TYPE_5__ menu_displaylist_info_t ;
typedef  enum menu_displaylist_ctl_state { ____Placeholder_menu_displaylist_ctl_state } menu_displaylist_ctl_state ;
struct TYPE_17__ {char* all_ext; } ;
typedef  TYPE_6__ core_info_list_t ;
struct TYPE_12__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_PLAIN ; 
 int PATH_MAX_LENGTH ; 
#define  PUSH_ARCHIVE_OPEN 131 
#define  PUSH_ARCHIVE_OPEN_DETECT_CORE 130 
#define  PUSH_DEFAULT 129 
#define  PUSH_DETECT_CORE_LIST 128 
 int /*<<< orphan*/  ST_DIR ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  core_info_get_list (TYPE_6__**) ; 
 int deferred_push_dlist (TYPE_5__*,int) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libretro_ffmpeg_retro_get_system_info (struct retro_system_info*) ; 
 int /*<<< orphan*/  libretro_imageviewer_retro_get_system_info (struct retro_system_info*) ; 
 int /*<<< orphan*/  libretro_mpv_retro_get_system_info (struct retro_system_info*) ; 
 scalar_t__ malloc (int) ; 
 int menu_cbs_exit () ; 
 TYPE_4__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  menu_setting_find_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_setting_get_browser_selection_type (int /*<<< orphan*/ ) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_find_elem (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_join_concat (char*,size_t,struct string_list*,char*) ; 
 struct string_list* string_list_new () ; 
 struct string_list* string_split (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int general_push(menu_displaylist_info_t *info,
      unsigned id, enum menu_displaylist_ctl_state state)
{
   char                      *newstring2 = NULL;
   core_info_list_t           *list      = NULL;
   settings_t                  *settings = config_get_ptr();
   menu_handle_t                  *menu  = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   core_info_get_list(&list);

   switch (id)
   {
      case PUSH_DEFAULT:
      case PUSH_DETECT_CORE_LIST:
         break;
      default:
         {
            char tmp_str[PATH_MAX_LENGTH];
            char tmp_str2[PATH_MAX_LENGTH];

            tmp_str[0] = '\0';
            tmp_str2[0] = '\0';

            fill_pathname_join(tmp_str, menu->scratch2_buf,
                  menu->scratch_buf, sizeof(tmp_str));
            fill_pathname_join(tmp_str2, menu->scratch2_buf,
                  menu->scratch_buf, sizeof(tmp_str2));

            if (!string_is_empty(info->path))
               free(info->path);
            if (!string_is_empty(info->label))
               free(info->label);

            info->path  = strdup(tmp_str);
            info->label = strdup(tmp_str2);
         }
         break;
   }

   info->type_default = FILE_TYPE_PLAIN;

   switch (id)
   {
      case PUSH_ARCHIVE_OPEN_DETECT_CORE:
      case PUSH_ARCHIVE_OPEN:
      case PUSH_DEFAULT:
         info->setting      = menu_setting_find_enum(info->enum_idx);
         break;
      default:
         break;
   }

   newstring2                     = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

   newstring2[0]                  = '\0';

   switch (id)
   {
      case PUSH_ARCHIVE_OPEN:
         {
            struct retro_system_info *system = 
               runloop_get_libretro_system_info();
            if (system)
            {
               if (!string_is_empty(system->valid_extensions))
                  strlcpy(newstring2, system->valid_extensions,
                        PATH_MAX_LENGTH * sizeof(char));
            }
         }
         break;
      case PUSH_DEFAULT:
         {
            bool new_exts_allocated               = false;
            char *new_exts                        = NULL;

            if (menu_setting_get_browser_selection_type(info->setting) == ST_DIR)
            {
            }
            else
            {
               struct retro_system_info *system = 
                  runloop_get_libretro_system_info();
               if (system && !string_is_empty(system->valid_extensions))
               {
                  new_exts           = strdup(system->valid_extensions);
                  new_exts_allocated = true;
               }
            }

            if (!new_exts)
               new_exts = info->exts;

            if (!string_is_empty(new_exts))
            {
               size_t path_size               = PATH_MAX_LENGTH * sizeof(char);
               struct string_list *str_list3  = string_split(new_exts, "|");

#ifdef HAVE_IBXM
               {
                  union string_list_elem_attr attr;
                  attr.i = 0;
                  string_list_append(str_list3, "s3m", attr);
                  string_list_append(str_list3, "mod", attr);
                  string_list_append(str_list3, "xm", attr);
               }
#endif
               string_list_join_concat(newstring2, path_size,
                     str_list3, "|");
               string_list_free(str_list3);

            }

            if (new_exts_allocated)
            {
               free(new_exts);

               if (new_exts == info->exts)
                  info->exts = NULL;
            }
         }
         break;
      case PUSH_ARCHIVE_OPEN_DETECT_CORE:
      case PUSH_DETECT_CORE_LIST:
         {
            union string_list_elem_attr attr;
            size_t path_size                 = PATH_MAX_LENGTH * sizeof(char);
            char *newstring                  = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
            struct string_list *str_list2    = string_list_new();
            struct retro_system_info *system = runloop_get_libretro_system_info();

            newstring[0]                     = '\0';
            attr.i                           = 0;

            if (system)
            {
               if (!string_is_empty(system->valid_extensions))
               {
                  unsigned x;
                  struct string_list *str_list    = string_split(system->valid_extensions, "|");

                  for (x = 0; x < str_list->size; x++)
                  {
                     const char *elem = str_list->elems[x].data;
                     string_list_append(str_list2, elem, attr);
                  }

                  string_list_free(str_list);
               }
            }

            if (!settings->bools.filter_by_current_core)
            {
               if (list && !string_is_empty(list->all_ext))
               {
                  unsigned x;
                  struct string_list *str_list    = string_split(list->all_ext, "|");

                  for (x = 0; x < str_list->size; x++)
                  {
                     if (!string_list_find_elem(str_list2, str_list->elems[x].data))
                     {
                        const char *elem = str_list->elems[x].data;
                        string_list_append(str_list2, elem, attr);
                     }
                  }

                  string_list_free(str_list);
               }
            }

            string_list_join_concat(newstring, path_size,
                  str_list2, "|");

            {
               struct string_list *str_list3  = string_split(newstring, "|");

#ifdef HAVE_IBXM
               {
                  union string_list_elem_attr attr;
                  attr.i = 0;
                  string_list_append(str_list3, "s3m", attr);
                  string_list_append(str_list3, "mod", attr);
                  string_list_append(str_list3, "xm", attr);
               }
#endif
               string_list_join_concat(newstring2, path_size,
                     str_list3, "|");
               string_list_free(str_list3);
            }
            free(newstring);
            string_list_free(str_list2);
         }
         break;
   }

   if (settings->bools.multimedia_builtin_mediaplayer_enable ||
         settings->bools.multimedia_builtin_imageviewer_enable)
   {
      struct retro_system_info sysinfo = {0};

      (void)sysinfo;
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
      if (settings->bools.multimedia_builtin_mediaplayer_enable)
      {
#if defined(HAVE_FFMPEG)
         libretro_ffmpeg_retro_get_system_info(&sysinfo);
#elif defined(HAVE_MPV)
         libretro_mpv_retro_get_system_info(&sysinfo);
#endif
         strlcat(newstring2, "|", PATH_MAX_LENGTH * sizeof(char));
         strlcat(newstring2, sysinfo.valid_extensions,
               PATH_MAX_LENGTH * sizeof(char));
      }
#endif
#ifdef HAVE_IMAGEVIEWER
      if (settings->bools.multimedia_builtin_imageviewer_enable)
      {
         libretro_imageviewer_retro_get_system_info(&sysinfo);
         strlcat(newstring2, "|", PATH_MAX_LENGTH * sizeof(char));
         strlcat(newstring2, sysinfo.valid_extensions,
               PATH_MAX_LENGTH * sizeof(char));
      }
#endif
   }

   if (!string_is_empty(newstring2))
   {
      if (!string_is_empty(info->exts))
         free(info->exts);
      info->exts = strdup(newstring2);
   }
   free(newstring2);

   return deferred_push_dlist(info, state);
}