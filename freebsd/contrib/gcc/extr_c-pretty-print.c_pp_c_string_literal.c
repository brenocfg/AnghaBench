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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 int TREE_STRING_LENGTH (int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_char (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  pp_doublequote (int /*<<< orphan*/ *) ; 

void
pp_c_string_literal (c_pretty_printer *pp, tree s)
{
  const char *p = TREE_STRING_POINTER (s);
  int n = TREE_STRING_LENGTH (s) - 1;
  int i;
  pp_doublequote (pp);
  for (i = 0; i < n; ++i)
    pp_c_char (pp, p[i]);
  pp_doublequote (pp);
}