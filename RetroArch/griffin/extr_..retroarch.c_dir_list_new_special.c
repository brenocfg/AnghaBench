#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
struct string_list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  show_hidden_files; } ;
struct TYPE_7__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  ext_shaders ;
typedef  int /*<<< orphan*/  ext_name ;
typedef  enum dir_list_type { ____Placeholder_dir_list_type } dir_list_type ;
struct TYPE_8__ {char* all_ext; } ;
typedef  TYPE_3__ core_info_list_t ;

/* Variables and functions */
#define  DIR_LIST_AUTOCONFIG 136 
#define  DIR_LIST_COLLECTIONS 135 
#define  DIR_LIST_CORES 134 
#define  DIR_LIST_CORE_INFO 133 
#define  DIR_LIST_DATABASES 132 
#define  DIR_LIST_NONE 131 
#define  DIR_LIST_PLAIN 130 
#define  DIR_LIST_RECURSIVE 129 
#define  DIR_LIST_SHADERS 128 
 int /*<<< orphan*/  RARCH_SHADER_CG ; 
 int /*<<< orphan*/  RARCH_SHADER_GLSL ; 
 int /*<<< orphan*/  RARCH_SHADER_SLANG ; 
 TYPE_2__* configuration_settings ; 
 int /*<<< orphan*/  core_info_get_list (TYPE_3__**) ; 
 struct string_list* dir_list_new (char const*,char const*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  frontend_driver_get_core_extension (char*,int) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_join_concat (char*,int,struct string_list*,char*) ; 
 struct string_list* string_list_new () ; 
 int /*<<< orphan*/  video_shader_is_supported (int /*<<< orphan*/ ) ; 

struct string_list *dir_list_new_special(const char *input_dir,
      enum dir_list_type type, const char *filter)
{
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   char ext_shaders[255];
#endif
   char ext_name[255];
   const char *exts                  = NULL;
   bool recursive                    = false;
   settings_t *settings              = configuration_settings;

   switch (type)
   {
      case DIR_LIST_AUTOCONFIG:
         exts = filter;
         break;
      case DIR_LIST_CORES:
         {
            ext_name[0]         = '\0';

            if (!frontend_driver_get_core_extension(ext_name, sizeof(ext_name)))
               return NULL;

            exts = ext_name;
         }
         break;
      case DIR_LIST_RECURSIVE:
         recursive = true;
         /* fall-through */
      case DIR_LIST_CORE_INFO:
         {
            core_info_list_t *list = NULL;
            core_info_get_list(&list);

            if (list)
               exts = list->all_ext;
         }
         break;
      case DIR_LIST_SHADERS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
         {
            union string_list_elem_attr attr;
            struct string_list *str_list     = string_list_new();

            if (!str_list)
               return NULL;

            ext_shaders[0]                   = '\0';

            attr.i = 0;

            if (video_shader_is_supported(RARCH_SHADER_CG))
            {
               string_list_append(str_list, "cgp", attr);
               string_list_append(str_list, "cg", attr);
            }

            if (video_shader_is_supported(RARCH_SHADER_GLSL))
            {
               string_list_append(str_list, "glslp", attr);
               string_list_append(str_list, "glsl", attr);
            }

            if (video_shader_is_supported(RARCH_SHADER_SLANG))
            {
               string_list_append(str_list, "slangp", attr);
               string_list_append(str_list, "slang", attr);
            }

            string_list_join_concat(ext_shaders, sizeof(ext_shaders), str_list, "|");
            string_list_free(str_list);
            exts = ext_shaders;
         }
#endif
         break;
      case DIR_LIST_COLLECTIONS:
         exts = "lpl";
         break;
      case DIR_LIST_DATABASES:
         exts = "rdb";
         break;
      case DIR_LIST_PLAIN:
         exts = filter;
         break;
      case DIR_LIST_NONE:
      default:
         return NULL;
   }

   return dir_list_new(input_dir, exts, false,
         settings->bools.show_hidden_files,
         type == DIR_LIST_CORE_INFO, recursive);
}