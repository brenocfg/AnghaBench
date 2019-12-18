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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  OPT_Wunused_parameter ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_USED (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
do_warn_unused_parameter (tree fn)
{
  tree decl;

  for (decl = DECL_ARGUMENTS (fn);
       decl; decl = TREE_CHAIN (decl))
    if (!TREE_USED (decl) && TREE_CODE (decl) == PARM_DECL
	&& DECL_NAME (decl) && !DECL_ARTIFICIAL (decl))
      warning (OPT_Wunused_parameter, "unused parameter %q+D", decl);
}