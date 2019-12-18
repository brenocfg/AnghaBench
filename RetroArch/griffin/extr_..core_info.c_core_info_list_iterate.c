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
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char*) ; 
 int /*<<< orphan*/  fill_pathname_base_noext (char*,char const*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ path_is_valid (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static config_file_t *core_info_list_iterate(
      const char *current_path,
      const char *path_basedir)
{
   size_t info_path_base_size = PATH_MAX_LENGTH * sizeof(char);
   char *info_path_base       = NULL;
   char *info_path            = NULL;
   config_file_t *conf        = NULL;

   if (!current_path)
      return NULL;

   info_path_base             = (char*)malloc(info_path_base_size);

   info_path_base[0] = '\0';

   fill_pathname_base_noext(info_path_base,
         current_path,
         info_path_base_size);

#if defined(RARCH_MOBILE) || (defined(RARCH_CONSOLE) && !defined(PSP) && !defined(_3DS) && !defined(VITA) && !defined(PS2) && !defined(HW_WUP))
   {
      char *substr = strrchr(info_path_base, '_');
      if (substr)
         *substr = '\0';
   }
#endif

   strlcat(info_path_base, ".info", info_path_base_size);

   info_path = (char*)malloc(info_path_base_size);
   fill_pathname_join(info_path,
         path_basedir,
         info_path_base, info_path_base_size);
   free(info_path_base);
   info_path_base = NULL;

   if (path_is_valid(info_path))
      conf = config_file_new_from_path_to_string(info_path);
   free(info_path);

   return conf;
}