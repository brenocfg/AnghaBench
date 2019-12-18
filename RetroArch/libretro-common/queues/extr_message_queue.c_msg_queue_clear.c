#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ptr; TYPE_3__* tmp_msg; TYPE_3__** elems; } ;
typedef  TYPE_1__ msg_queue_t ;
struct TYPE_5__ {struct TYPE_5__* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

void msg_queue_clear(msg_queue_t *queue)
{
   size_t i;

   if (!queue)
      return;

   for (i = 1; i < queue->ptr; i++)
   {
      if (queue->elems[i])
      {
         free(queue->elems[i]->msg);
         free(queue->elems[i]);
         queue->elems[i] = NULL;
      }
   }
   queue->ptr = 1;
   free(queue->tmp_msg);
   queue->tmp_msg = NULL;
}