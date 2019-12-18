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
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char const*) ; 
 scalar_t__ config_get_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

bool core_info_get_display_name(const char *path, char *s, size_t len)
{
   char       *tmp     = NULL;
   config_file_t *conf = config_file_new_from_path_to_string(path);

   if (!conf)
      return false;

   if (config_get_string(conf, "display_name", &tmp))
   {
      strlcpy(s, tmp, len);
      free(tmp);
   }

   config_file_free(conf);
   return true;
}