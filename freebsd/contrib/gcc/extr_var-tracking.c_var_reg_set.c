#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_6__ {TYPE_2__** regs; } ;
typedef  TYPE_1__ dataflow_set ;
typedef  TYPE_2__* attrs ;
struct TYPE_7__ {scalar_t__ decl; scalar_t__ offset; struct TYPE_7__* next; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 size_t REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrs_list_insert (TYPE_2__**,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_variable_part (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ var_debug_decl (scalar_t__) ; 

__attribute__((used)) static void
var_reg_set (dataflow_set *set, rtx loc)
{
  tree decl = REG_EXPR (loc);
  HOST_WIDE_INT offset = REG_OFFSET (loc);
  attrs node;

  decl = var_debug_decl (decl);

  for (node = set->regs[REGNO (loc)]; node; node = node->next)
    if (node->decl == decl && node->offset == offset)
      break;
  if (!node)
    attrs_list_insert (&set->regs[REGNO (loc)], decl, offset, loc);
  set_variable_part (set, loc, decl, offset);
}