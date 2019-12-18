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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ dependent_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline void
pp_cxx_template_keyword_if_needed (cxx_pretty_printer *pp, tree scope, tree t)
{
  if (TREE_CODE (t) == TEMPLATE_ID_EXPR
      && TYPE_P (scope) && dependent_type_p (scope))
    pp_cxx_identifier (pp, "template");
}