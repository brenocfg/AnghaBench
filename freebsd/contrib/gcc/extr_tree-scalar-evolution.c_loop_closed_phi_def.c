#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {TYPE_1__* single_exit; } ;
typedef  TYPE_1__* edge ;
struct TYPE_3__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 struct loop* loop_containing_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
loop_closed_phi_def (tree var)
{
  struct loop *loop;
  edge exit;
  tree phi;

  if (var == NULL_TREE
      || TREE_CODE (var) != SSA_NAME)
    return NULL_TREE;

  loop = loop_containing_stmt (SSA_NAME_DEF_STMT (var));
  exit = loop->single_exit;
  if (!exit)
    return NULL_TREE;

  for (phi = phi_nodes (exit->dest); phi; phi = PHI_CHAIN (phi))
    if (PHI_ARG_DEF_FROM_EDGE (phi, exit) == var)
      return PHI_RESULT (phi);

  return NULL_TREE;
}