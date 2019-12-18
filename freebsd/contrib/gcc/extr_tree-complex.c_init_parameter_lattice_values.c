#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  VARYING ; 
 int /*<<< orphan*/  VEC_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  complex_lattice_t ; 
 int /*<<< orphan*/  complex_lattice_values ; 
 scalar_t__ default_def (scalar_t__) ; 
 scalar_t__ is_complex_reg (scalar_t__) ; 
 int /*<<< orphan*/ * var_ann (scalar_t__) ; 

__attribute__((used)) static void
init_parameter_lattice_values (void)
{
  tree parm;

  for (parm = DECL_ARGUMENTS (cfun->decl); parm ; parm = TREE_CHAIN (parm))
    if (is_complex_reg (parm) && var_ann (parm) != NULL)
      {
	tree ssa_name = default_def (parm);
	VEC_replace (complex_lattice_t, complex_lattice_values,
		     SSA_NAME_VERSION (ssa_name), VARYING);
      }
}