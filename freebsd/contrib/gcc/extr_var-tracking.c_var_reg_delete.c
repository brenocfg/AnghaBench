#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_7__ {TYPE_2__** regs; } ;
typedef  TYPE_1__ dataflow_set ;
typedef  TYPE_2__* attrs ;
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  decl; int /*<<< orphan*/  loc; struct TYPE_8__* next; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EXPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrs_pool ; 
 int /*<<< orphan*/  clobber_variable_part (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_variable_part (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  var_debug_decl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
var_reg_delete (dataflow_set *set, rtx loc, bool clobber)
{
  attrs *reg = &set->regs[REGNO (loc)];
  attrs node, next;

  if (clobber)
    {
      tree decl = REG_EXPR (loc);
      HOST_WIDE_INT offset = REG_OFFSET (loc);

      decl = var_debug_decl (decl);

      clobber_variable_part (set, NULL, decl, offset);
    }

  for (node = *reg; node; node = next)
    {
      next = node->next;
      delete_variable_part (set, node->loc, node->decl, node->offset);
      pool_free (attrs_pool, node);
    }
  *reg = NULL;
}