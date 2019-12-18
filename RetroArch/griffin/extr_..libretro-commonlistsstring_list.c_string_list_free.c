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
struct string_list {size_t size; struct string_list* elems; struct string_list* userdata; struct string_list* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct string_list*) ; 

void string_list_free(struct string_list *list)
{
   size_t i;
   if (!list)
      return;

   if (list->elems)
   {
      for (i = 0; i < list->size; i++)
      {
         if (list->elems[i].data)
            free(list->elems[i].data);
         if (list->elems[i].userdata)
            free(list->elems[i].userdata);
         list->elems[i].data     = NULL;
         list->elems[i].userdata = NULL;
      }

      free(list->elems);
   }

   list->elems = NULL;
   free(list);
}