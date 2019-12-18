#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* dir; char* path; size_t len; char* s; scalar_t__ data; } ;
typedef  TYPE_1__ menu_content_ctx_defer_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ core_info_t ;
typedef  int /*<<< orphan*/  core_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_info_get_current_core (TYPE_2__**) ; 
 int /*<<< orphan*/  core_info_list_get_supported_cores (int /*<<< orphan*/ *,char*,TYPE_2__ const**,size_t*) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char const*,size_t) ; 
 scalar_t__ path_is_compressed_file (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool menu_content_find_first_core(menu_content_ctx_defer_info_t *def_info,
      bool load_content_with_current_core,
      char *new_core_path, size_t len)
{
   const core_info_t *info                 = NULL;
   size_t supported                        = 0;
   core_info_list_t *core_info             = (core_info_list_t*)def_info->data;
   const char *default_info_dir            = def_info->dir;

   if (!string_is_empty(default_info_dir))
   {
      const char *default_info_path = def_info->path;
      size_t default_info_length    = def_info->len;

      if (!string_is_empty(default_info_path))
         fill_pathname_join(def_info->s,
               default_info_dir, default_info_path,
               default_info_length);

#ifdef HAVE_COMPRESSION
      if (path_is_compressed_file(default_info_dir))
      {
         size_t len = strlen(default_info_dir);
         /* In case of a compressed archive, we have to join with a hash */
         /* We are going to write at the position of dir: */
         def_info->s[len] = '#';
      }
#endif
   }

   if (core_info)
      core_info_list_get_supported_cores(core_info,
            def_info->s, &info,
            &supported);

   /* We started the menu with 'Load Content', we are
    * going to use the current core to load this. */
   if (load_content_with_current_core)
   {
      core_info_get_current_core((core_info_t**)&info);
      if (info)
      {
#if 0
         RARCH_LOG("[lobby] use the current core (%s) to load this content...\n",
               info->path);
#endif
         supported = 1;
      }
   }

   /* There are multiple deferred cores and a
    * selection needs to be made from a list, return 0. */
   if (supported != 1)
      return false;

    if (info)
      strlcpy(new_core_path, info->path, len);

   return true;
}