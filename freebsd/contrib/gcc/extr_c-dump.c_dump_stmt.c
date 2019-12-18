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
typedef  int /*<<< orphan*/  dump_info_p ;

/* Variables and functions */
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LINENO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
dump_stmt (dump_info_p di, tree t)
{
  if (EXPR_HAS_LOCATION (t))
    dump_int (di, "line", EXPR_LINENO (t));
}