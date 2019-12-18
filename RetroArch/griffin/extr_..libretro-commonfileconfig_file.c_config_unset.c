#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct config_entry_list {int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; } ;
struct TYPE_4__ {struct config_entry_list* entries; } ;
typedef  TYPE_1__ config_file_t ;

/* Variables and functions */
 struct config_entry_list* config_get_entry (TYPE_1__*,char const*,struct config_entry_list**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void config_unset(config_file_t *conf, const char *key)
{
   struct config_entry_list *last  = conf->entries;
   struct config_entry_list *entry = config_get_entry(conf, key, &last);

   if (!entry)
      return;

   entry->key   = NULL;
   entry->value = NULL;
   free(entry->key);
   free(entry->value);
}