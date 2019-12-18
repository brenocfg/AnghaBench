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
struct TYPE_3__ {int /*<<< orphan*/ * tail; struct aic7xxx_scb* head; } ;
typedef  TYPE_1__ scb_queue_type ;

/* Variables and functions */

__attribute__((used)) static inline struct aic7xxx_scb *
scbq_remove_head(volatile scb_queue_type *queue)
{
  struct aic7xxx_scb * scbp;

  scbp = queue->head;
  if (queue->head != NULL)
    queue->head = queue->head->q_next;
  if (queue->head == NULL)       /* If list is now empty, update tail. */
    queue->tail = NULL;
  return(scbp);
}