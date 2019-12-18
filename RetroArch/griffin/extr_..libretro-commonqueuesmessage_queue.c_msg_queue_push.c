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
struct queue_elem {unsigned int prio; unsigned int duration; int /*<<< orphan*/ * msg; } ;
struct TYPE_3__ {size_t ptr; size_t size; struct queue_elem** elems; } ;
typedef  TYPE_1__ msg_queue_t ;
typedef  enum message_queue_icon { ____Placeholder_message_queue_icon } message_queue_icon ;
typedef  enum message_queue_category { ____Placeholder_message_queue_category } message_queue_category ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

void msg_queue_push(msg_queue_t *queue, const char *msg,
      unsigned prio, unsigned duration,
      char *title,
      enum message_queue_icon icon, enum message_queue_category category)
{
   size_t tmp_ptr = 0;
   struct queue_elem *new_elem = NULL;

   if (!queue || queue->ptr >= queue->size)
      return;

   new_elem                      = (struct queue_elem*)
      calloc(1, sizeof(struct queue_elem));
   if (!new_elem)
      return;

   new_elem->prio                = prio;
   new_elem->duration            = duration;
   new_elem->msg                 = msg ? strdup(msg) : NULL;

   queue->elems[queue->ptr]      = new_elem;

   tmp_ptr                       = queue->ptr++;

   while (tmp_ptr > 1)
   {
      struct queue_elem *parent  = queue->elems[tmp_ptr >> 1];
      struct queue_elem *child   = queue->elems[tmp_ptr];

      if (child->prio <= parent->prio)
         break;

      queue->elems[tmp_ptr >> 1] = child;
      queue->elems[tmp_ptr]      = parent;

      tmp_ptr >>= 1;
   }
}