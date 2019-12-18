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
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  build_empty_stmt () ; 
 scalar_t__ default_def (scalar_t__) ; 
 scalar_t__ make_ssa_name (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_def (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline tree
get_default_def_for (tree sym)
{
  tree ddef = default_def (sym);

  if (ddef == NULL_TREE)
    {
      ddef = make_ssa_name (sym, build_empty_stmt ());
      set_default_def (sym, ddef);
    }

  return ddef;
}