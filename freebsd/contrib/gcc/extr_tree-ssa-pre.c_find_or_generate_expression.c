#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct TYPE_3__ {int /*<<< orphan*/ * expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVAIL_OUT (int /*<<< orphan*/ ) ; 
 TYPE_2__* VALUE_HANDLE_EXPR_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bitmap_find_leader (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_PRE_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_expression_by_pieces (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
find_or_generate_expression (basic_block block, tree expr, tree stmts)
{
  tree genop = bitmap_find_leader (AVAIL_OUT (block), expr);

  /* If it's still NULL, it must be a complex expression, so generate
     it recursively.  */
  if (genop == NULL)
    {
      genop = VALUE_HANDLE_EXPR_SET (expr)->head->expr;

      gcc_assert (can_PRE_operation (genop));
      genop = create_expression_by_pieces (block, genop, stmts);
    }
  return genop;
}