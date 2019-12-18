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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 size_t BUILT_IN_GOMP_BARRIER ; 
 int /*<<< orphan*/ * built_in_decls ; 
 int /*<<< orphan*/  finish_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 

void
finish_omp_barrier (void)
{
  tree fn = built_in_decls[BUILT_IN_GOMP_BARRIER];
  tree stmt = finish_call_expr (fn, NULL, false, false);
  finish_expr_stmt (stmt);
}