#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* data; } ;
typedef  TYPE_1__ task_retriever_info_t ;
struct TYPE_11__ {scalar_t__ handler; int element_size; TYPE_1__* list; int /*<<< orphan*/  (* func ) (TYPE_3__*,TYPE_1__*) ;} ;
typedef  TYPE_2__ task_retriever_data_t ;
struct TYPE_12__ {scalar_t__ handler; struct TYPE_12__* next; } ;
typedef  TYPE_3__ retro_task_t ;
struct TYPE_13__ {TYPE_3__* front; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_1__*) ; 
 TYPE_4__ tasks_running ; 

__attribute__((used)) static void retro_task_regular_retrieve(task_retriever_data_t *data)
{
   retro_task_t *task          = NULL;
   task_retriever_info_t *tail = NULL;

   /* Parse all running tasks and handle matching handlers */
   for (task = tasks_running.front; task != NULL; task = task->next)
   {
      task_retriever_info_t *info = NULL;
      if (task->handler != data->handler)
         continue;

      /* Create new link */
      info       = (task_retriever_info_t*)malloc(sizeof(task_retriever_info_t));
      info->data = malloc(data->element_size);
      info->next = NULL;

      /* Call retriever function and fill info-specific data */
      if (!data->func(task, info->data))
      {
         free(info->data);
         free(info);
         continue;
      }

      /* Add link to list */
      if (data->list)
      {
         if (tail)
         {
            tail->next = info;
            tail       = tail->next;
         }
         else
            tail       = info;
      }
      else
      {
         data->list    = info;
         tail          = data->list;
      }
   }
}