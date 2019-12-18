#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* use_operand_p ;
struct TYPE_7__ {TYPE_2__* next; } ;
struct TYPE_9__ {TYPE_2__* imm_use; TYPE_1__ iter_node; } ;
typedef  TYPE_3__ imm_use_iterator ;
struct TYPE_8__ {struct TYPE_8__* next; } ;

/* Variables and functions */
 scalar_t__ end_readonly_imm_use_p (TYPE_3__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline use_operand_p
next_readonly_imm_use (imm_use_iterator *imm)
{
  use_operand_p old = imm->imm_use;

#ifdef ENABLE_CHECKING
  /* If this assertion fails, it indicates the 'next' pointer has changed 
     since we the last bump.  This indicates that the list is being modified
     via stmt changes, or SET_USE, or somesuch thing, and you need to be
     using the SAFE version of the iterator.  */
  gcc_assert (imm->iter_node.next == old->next);
  imm->iter_node.next = old->next->next;
#endif

  imm->imm_use = old->next;
  if (end_readonly_imm_use_p (imm))
    return old;
  return imm->imm_use;
}