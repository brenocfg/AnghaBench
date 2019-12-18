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
 int config_get_int (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,int /*<<< orphan*/ ,char const*,char,int) ; 

int config_userdata_get_int(void *userdata, const char *key_str,
      int *value, int default_value)
{
   bool got;
   char key[2][256];
   struct config_file_userdata *usr = (struct config_file_userdata*)userdata;

   fill_pathname_join_delim(key[0], usr->prefix[0], key_str, '_', sizeof(key[0]));
   fill_pathname_join_delim(key[1], usr->prefix[1], key_str, '_', sizeof(key[1]));

   got = config_get_int  (usr->conf, key[0], value);
   got = got || config_get_int(usr->conf, key[1], value);

   if (!got)
      *value = default_value;
   return got;
}