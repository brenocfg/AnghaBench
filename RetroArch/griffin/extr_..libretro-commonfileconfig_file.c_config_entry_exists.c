#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct config_entry_list {struct config_entry_list* next; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {struct config_entry_list* entries; } ;
typedef  TYPE_1__ config_file_t ;

/* Variables and functions */
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

bool config_entry_exists(config_file_t *conf, const char *entry)
{
   struct config_entry_list *list = conf->entries;

   while (list)
   {
      if (string_is_equal(entry, list->key))
         return true;
      list = list->next;
   }

   return false;
}