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
 int /*<<< orphan*/  finalize_ssa_defs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_ssa_uses (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_ssa_v_may_defs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_ssa_v_must_defs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_ssa_vuses (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
finalize_ssa_stmt_operands (tree stmt)
{
  finalize_ssa_defs (stmt);
  finalize_ssa_uses (stmt);
  finalize_ssa_v_must_defs (stmt);
  finalize_ssa_v_may_defs (stmt);
  finalize_ssa_vuses (stmt);
}