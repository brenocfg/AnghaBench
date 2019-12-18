#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_3__* edge ;
struct TYPE_8__ {TYPE_2__* dest; TYPE_1__* src; } ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {int index; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 scalar_t__ PARM_DECL ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  bsi_insert_on_edge (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_is_used (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_copy_on_edge (edge e, tree dest, tree src)
{
  tree copy;

  copy = build2 (MODIFY_EXPR, TREE_TYPE (dest), dest, src);
  set_is_used (dest);

  if (TREE_CODE (src) == ADDR_EXPR)
    src = TREE_OPERAND (src, 0);
  if (TREE_CODE (src) == VAR_DECL || TREE_CODE (src) == PARM_DECL)
    set_is_used (src);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file,
	       "Inserting a copy on edge BB%d->BB%d :",
	       e->src->index,
	       e->dest->index);
      print_generic_expr (dump_file, copy, dump_flags);
      fprintf (dump_file, "\n");
    }

  bsi_insert_on_edge (e, copy);
}