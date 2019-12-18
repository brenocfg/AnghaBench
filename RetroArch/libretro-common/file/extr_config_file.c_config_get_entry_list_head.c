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
struct config_file_entry {int /*<<< orphan*/  next; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct config_entry_list {int /*<<< orphan*/  next; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {struct config_entry_list* entries; } ;
typedef  TYPE_1__ config_file_t ;

/* Variables and functions */

bool config_get_entry_list_head(config_file_t *conf,
      struct config_file_entry *entry)
{
   const struct config_entry_list *head = conf->entries;

   if (!head)
      return false;

   entry->key   = head->key;
   entry->value = head->value;
   entry->next  = head->next;
   return true;
}