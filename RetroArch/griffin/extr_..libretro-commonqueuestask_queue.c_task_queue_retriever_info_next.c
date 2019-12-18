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
struct TYPE_3__ {struct TYPE_3__* next; void* data; } ;
typedef  TYPE_1__ task_retriever_info_t ;

/* Variables and functions */

void *task_queue_retriever_info_next(task_retriever_info_t **link)
{
   void *data = NULL;

   /* Grab data and move to next link */
   if (*link)
   {
      data = (*link)->data;
      *link = (*link)->next;
   }

   return data;
}