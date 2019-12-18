#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_7__ {scalar_t__ stmt; } ;
typedef  TYPE_1__ ssa_use_operand_t ;

/* Variables and functions */
 int /*<<< orphan*/  link_imm_use (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relink_imm_use (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static inline void
relink_imm_use_stmt (ssa_use_operand_t *linknode, ssa_use_operand_t *old, tree stmt)
{
  if (stmt)
    relink_imm_use (linknode, old);
  else
    link_imm_use (linknode, NULL);
  linknode->stmt = stmt;
}