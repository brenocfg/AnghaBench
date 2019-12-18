#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* next; TYPE_1__* prev; } ;
typedef  TYPE_3__ ssa_use_operand_t ;
struct TYPE_6__ {TYPE_1__* prev; } ;
struct TYPE_5__ {TYPE_2__* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void
delink_imm_use (ssa_use_operand_t *linknode)
{
  /* Return if this node is not in a list.  */
  if (linknode->prev == NULL)
    return;

  linknode->prev->next = linknode->next;
  linknode->next->prev = linknode->prev;
  linknode->prev = NULL;
  linknode->next = NULL;
}