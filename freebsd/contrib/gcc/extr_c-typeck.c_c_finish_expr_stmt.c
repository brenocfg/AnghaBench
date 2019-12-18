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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_process_expr_stmt (int /*<<< orphan*/ *) ; 

tree
c_finish_expr_stmt (tree expr)
{
  if (expr)
    return add_stmt (c_process_expr_stmt (expr));
  else
    return NULL;
}