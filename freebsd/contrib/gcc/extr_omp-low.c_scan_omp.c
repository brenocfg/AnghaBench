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
typedef  int /*<<< orphan*/  wi ;
typedef  int /*<<< orphan*/  tree ;
struct walk_stmt_info {int want_locations; int /*<<< orphan*/  want_bind_expr; int /*<<< orphan*/ * info; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  omp_context ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  memset (struct walk_stmt_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scan_omp_1 ; 
 int /*<<< orphan*/  walk_stmts (struct walk_stmt_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scan_omp (tree *stmt_p, omp_context *ctx)
{
  location_t saved_location;
  struct walk_stmt_info wi;

  memset (&wi, 0, sizeof (wi));
  wi.callback = scan_omp_1;
  wi.info = ctx;
  wi.want_bind_expr = (ctx != NULL);
  wi.want_locations = true;

  saved_location = input_location;
  walk_stmts (&wi, stmt_p);
  input_location = saved_location;
}