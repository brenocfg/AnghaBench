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
struct c_expr {scalar_t__ original_code; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn_init (char*) ; 

void
maybe_warn_string_init (tree type, struct c_expr expr)
{
  if (pedantic
      && TREE_CODE (type) == ARRAY_TYPE
      && TREE_CODE (expr.value) == STRING_CST
      && expr.original_code != STRING_CST)
    pedwarn_init ("array initialized from parenthesized string constant");
}