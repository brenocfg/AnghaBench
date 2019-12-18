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
struct config_file_userdata {int /*<<< orphan*/  conf; int /*<<< orphan*/ * prefix; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 scalar_t__ config_get_string (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,int /*<<< orphan*/ ,char const*,char,int) ; 
 char* strdup (char const*) ; 

int config_userdata_get_string(void *userdata, const char *key_str,
      char **output, const char *default_output)
{
   char key[2][256];
   struct config_file_userdata *usr = (struct config_file_userdata*)userdata;
   char *str = NULL;
   fill_pathname_join_delim(key[0], usr->prefix[0], key_str, '_', sizeof(key[0]));
   fill_pathname_join_delim(key[1], usr->prefix[1], key_str, '_', sizeof(key[1]));

   if (  config_get_string(usr->conf, key[0], &str) ||
         config_get_string(usr->conf, key[1], &str))
   {
      *output = str;
      return true;
   }

   *output = strdup(default_output);
   return false;
}