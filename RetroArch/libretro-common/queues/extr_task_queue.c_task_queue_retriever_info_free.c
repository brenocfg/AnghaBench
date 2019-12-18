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
struct TYPE_4__ {struct TYPE_4__* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ task_retriever_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void task_queue_retriever_info_free(task_retriever_info_t *list)
{
   task_retriever_info_t *info;

   /* Free links including retriever-specific data */
   while (list)
   {
      info = list->next;
      free(list->data);
      free(list);
      list = info;
   }
}