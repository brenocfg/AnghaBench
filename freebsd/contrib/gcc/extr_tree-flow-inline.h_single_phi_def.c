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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 int SSA_OP_DEF ; 
 int SSA_OP_VIRTUAL_DEFS ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
single_phi_def (tree stmt, int flags)
{
  tree def = PHI_RESULT (stmt);
  if ((flags & SSA_OP_DEF) && is_gimple_reg (def)) 
    return def;
  if ((flags & SSA_OP_VIRTUAL_DEFS) && !is_gimple_reg (def))
    return def;
  return NULL_TREE;
}