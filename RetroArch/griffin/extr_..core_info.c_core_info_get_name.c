#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_1__* elems; } ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 scalar_t__ config_get_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * core_info_list_iterate (char*,char const*) ; 
 int /*<<< orphan*/  dir_list_free (struct string_list*) ; 
 struct string_list* dir_list_new (char const*,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

void core_info_get_name(const char *path, char *s, size_t len,
      const char *path_info, const char *dir_cores,
      const char *exts, bool dir_show_hidden_files,
      bool get_display_name)
{
   size_t i;
   const char       *path_basedir   = !string_is_empty(path_info) ?
      path_info : dir_cores;
   struct string_list *contents     = dir_list_new(
         dir_cores, exts, false, dir_show_hidden_files, false, false);
   const char *core_path_basename   = path_basename(path);

   if (!contents)
      return;

   for (i = 0; i < contents->size; i++)
   {
      config_file_t *conf             = NULL;
      char *new_core_name             = NULL;
      const char *current_path        = contents->elems[i].data;

      if (!string_is_equal(path_basename(current_path), core_path_basename))
         continue;

      conf = core_info_list_iterate(contents->elems[i].data,
               path_basedir);

      if (!conf)
         continue;

      if (config_get_string(conf, get_display_name 
               ? "display_name" : "corename",
            &new_core_name))
      {
         strlcpy(s, new_core_name, len);
         free(new_core_name);
      }

      config_file_free(conf);
      break;
   }

   dir_list_free(contents);
   contents = NULL;
}