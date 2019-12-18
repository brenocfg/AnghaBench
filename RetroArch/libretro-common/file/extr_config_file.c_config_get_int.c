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
 struct config_entry_list* config_get_entry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool config_get_int(config_file_t *conf, const char *key, int *in)
{
   const struct config_entry_list *entry = config_get_entry(conf, key, NULL);
   errno = 0;

   if (entry)
   {
      int val = (int)strtol(entry->value, NULL, 0);

      if (errno == 0)
      {
         *in = val;
         return true;
      }
   }

   return false;
}