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
typedef  TYPE_1__* use_operand_p ;
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ stmt; int /*<<< orphan*/ * use; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_imm_use (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_virtual_use_link (use_operand_p ptr, tree stmt)
{
  /*  fold_stmt may have changed the stmt pointers.  */
  if (ptr->stmt != stmt)
    ptr->stmt = stmt;

  /* If this use isn't in a list, add it to the correct list.  */
  if (!ptr->prev)
    link_imm_use (ptr, *(ptr->use));
}