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
struct config_entry_list {int readonly; struct config_entry_list* next; } ;
struct TYPE_4__ {struct config_entry_list* tail; struct config_entry_list* entries; } ;
typedef  TYPE_1__ config_file_t ;

/* Variables and functions */

__attribute__((used)) static void add_child_list(config_file_t *parent, config_file_t *child)
{
   struct config_entry_list *list = child->entries;
   if (parent->entries)
   {
      struct config_entry_list *head = parent->entries;
      while (head->next)
         head = head->next;

      /* set list readonly */
      while (list)
      {
         list->readonly = true;
         list           = list->next;
      }
      head->next        = child->entries;
   }
   else
   {
      /* set list readonly */
      while (list)
      {
         list->readonly = true;
         list           = list->next;
      }
      parent->entries   = child->entries;
   }

   child->entries = NULL;

   /* Rebase tail. */
   if (parent->entries)
   {
      struct config_entry_list *head =
         (struct config_entry_list*)parent->entries;

      while (head->next)
         head = head->next;
      parent->tail = head;
   }
   else
      parent->tail = NULL;
}