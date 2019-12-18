#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/ * prev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * last; TYPE_2__* first; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ MMAL_LIST_T ;
typedef  TYPE_2__ MMAL_LIST_ELEMENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_list_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_list_unlock (TYPE_1__*) ; 

MMAL_LIST_ELEMENT_T* mmal_list_pop_front(MMAL_LIST_T *list)
{
   MMAL_LIST_ELEMENT_T *element;

   mmal_list_lock(list);

   element = list->first;
   if (element != NULL)
   {
      list->length--;

      list->first = element->next;
      if (list->first)
         list->first->prev = NULL;
      else
         list->last = NULL; /* list is now empty */

      element->prev = NULL;
      element->next = NULL;
   }

   mmal_list_unlock(list);

   return element;
}