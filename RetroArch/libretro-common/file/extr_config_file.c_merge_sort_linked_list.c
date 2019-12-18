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
struct config_entry_list {struct config_entry_list* next; } ;

/* Variables and functions */

__attribute__((used)) static struct config_entry_list* merge_sort_linked_list(
         struct config_entry_list *list, int (*compare)(
         struct config_entry_list *one,struct config_entry_list *two))
{
   struct config_entry_list
         *right  = list,
         *temp   = list,
         *last   = list,
         *result = 0,
         *next   = 0,
         *tail   = 0;

   /* Trivial case. */
   if (!list || !list->next)
      return list;

   /* Find halfway through the list (by running two pointers,
    * one at twice the speed of the other). */
   while (temp && temp->next)
   {
      last  = right;
      right = right->next;
      temp  = temp->next->next;
   }

   /* Break the list in two. (prev pointers are broken here,
    * but we fix later) */
   last->next = 0;

   /* Recurse on the two smaller lists: */
   list = merge_sort_linked_list(list, compare);
   right = merge_sort_linked_list(right, compare);

   /* Merge: */
   while (list || right)
   {
      /* Take from empty lists, or compare: */
      if (!right)
      {
         next = list;
         list = list->next;
      }
      else if (!list)
      {
         next = right;
         right = right->next;
      }
      else if (compare(list, right) < 0)
      {
         next = list;
         list = list->next;
      }
      else
      {
         next = right;
         right = right->next;
      }

      if (!result)
         result = next;
      else
         tail->next = next;

      tail = next;
   }

   return result;
}