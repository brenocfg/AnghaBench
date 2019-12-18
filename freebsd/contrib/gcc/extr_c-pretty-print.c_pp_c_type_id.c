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
 int /*<<< orphan*/  pp_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_specifier_qualifier_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_type_id (c_pretty_printer *pp, tree t)
{
  pp_c_specifier_qualifier_list (pp, t);
  pp_abstract_declarator (pp, t);
}