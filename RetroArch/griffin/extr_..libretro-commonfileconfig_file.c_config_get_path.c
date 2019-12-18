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
struct config_entry_list {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 scalar_t__ config_get_array (int /*<<< orphan*/ *,char const*,char*,size_t) ; 
 struct config_entry_list* config_get_entry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_pathname_expand_special (char*,int /*<<< orphan*/ ,size_t) ; 

bool config_get_path(config_file_t *conf, const char *key,
      char *buf, size_t size)
{
#if defined(RARCH_CONSOLE) || !defined(RARCH_INTERNAL)
   if (config_get_array(conf, key, buf, size))
      return true;
#else
   const struct config_entry_list *entry = config_get_entry(conf, key, NULL);

   if (entry)
   {
      fill_pathname_expand_special(buf, entry->value, size);
      return true;
   }
#endif
   return false;
}