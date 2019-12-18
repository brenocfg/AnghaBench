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
struct aic7xxx_scb {struct aic7xxx_scb* q_next; } ;
struct TYPE_3__ {struct aic7xxx_scb* tail; struct aic7xxx_scb* head; } ;
typedef  TYPE_1__ scb_queue_type ;

/* Variables and functions */

__attribute__((used)) static inline void
scbq_insert_tail(volatile scb_queue_type *queue, struct aic7xxx_scb *scb)
{
  scb->q_next = NULL;
  if (queue->tail != NULL)       /* Add the scb at the end of the list. */
    queue->tail->q_next = scb;
  queue->tail = scb;             /* Update the tail. */
  if (queue->head == NULL)       /* If list was empty, update head. */
    queue->head = queue->tail;
}