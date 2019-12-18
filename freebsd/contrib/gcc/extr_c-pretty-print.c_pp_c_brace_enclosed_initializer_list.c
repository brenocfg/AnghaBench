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
 int /*<<< orphan*/  pp_c_initializer_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_left_brace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_brace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_c_brace_enclosed_initializer_list (c_pretty_printer *pp, tree l)
{
  pp_c_left_brace (pp);
  pp_c_initializer_list (pp, l);
  pp_c_right_brace (pp);
}