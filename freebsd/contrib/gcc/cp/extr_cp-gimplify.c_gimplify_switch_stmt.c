#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_EXPR ; 
 scalar_t__ SWITCH_STMT_BODY (scalar_t__) ; 
 int /*<<< orphan*/  SWITCH_STMT_COND (scalar_t__) ; 
 int /*<<< orphan*/  SWITCH_STMT_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  bc_break ; 
 scalar_t__ begin_bc_block (int /*<<< orphan*/ ) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_empty_stmt () ; 
 scalar_t__ finish_bc_block (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gimplify_stmt (scalar_t__*) ; 
 int /*<<< orphan*/  input_location ; 

__attribute__((used)) static void
gimplify_switch_stmt (tree *stmt_p)
{
  tree stmt = *stmt_p;
  tree break_block, body;
  location_t stmt_locus = input_location;

  break_block = begin_bc_block (bc_break);

  body = SWITCH_STMT_BODY (stmt);
  if (!body)
    body = build_empty_stmt ();

  *stmt_p = build3 (SWITCH_EXPR, SWITCH_STMT_TYPE (stmt),
		    SWITCH_STMT_COND (stmt), body, NULL_TREE);
  SET_EXPR_LOCATION (*stmt_p, stmt_locus);
  gimplify_stmt (stmt_p);

  *stmt_p = finish_bc_block (bc_break, break_block, *stmt_p);
}