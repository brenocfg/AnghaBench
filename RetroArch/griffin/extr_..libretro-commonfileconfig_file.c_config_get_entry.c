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
struct config_entry_list {int /*<<< orphan*/  key; struct config_entry_list* next; } ;
struct TYPE_3__ {struct config_entry_list* entries; } ;
typedef  TYPE_1__ config_file_t ;

/* Variables and functions */
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct config_entry_list *config_get_entry(
      const config_file_t *conf,
      const char *key, struct config_entry_list **prev)
{
   struct config_entry_list *entry    = NULL;
   struct config_entry_list *previous = prev ? *prev : NULL;

   for (entry = conf->entries; entry; entry = entry->next)
   {
      if (string_is_equal(key, entry->key))
         return entry;

      previous = entry;
   }

   if (prev)
      *prev = previous;

   return NULL;
}