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

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MTAG_GLOBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MTAG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
unmodifiable_var_p (tree var)
{
  if (TREE_CODE (var) == SSA_NAME)
    var = SSA_NAME_VAR (var);

  if (MTAG_P (var))
    return TREE_READONLY (var) && (TREE_STATIC (var) || MTAG_GLOBAL (var));

  return TREE_READONLY (var) && (TREE_STATIC (var) || DECL_EXTERNAL (var));
}