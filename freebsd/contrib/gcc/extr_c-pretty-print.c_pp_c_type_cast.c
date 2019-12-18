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
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_c_type_cast (c_pretty_printer *pp, tree t)
{
  pp_c_left_paren (pp);
  pp_type_id (pp, t);
  pp_c_right_paren (pp);
}