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
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ OVERLOAD ; 
 int /*<<< orphan*/  OVL_CURRENT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_qualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pp_cxx_id_expression (cxx_pretty_printer *pp, tree t)
{
  if (TREE_CODE (t) == OVERLOAD)
    t = OVL_CURRENT (t);
  if (DECL_P (t) && DECL_CONTEXT (t))
    pp_cxx_qualified_id (pp, t);
  else
    pp_cxx_unqualified_id (pp, t);
}