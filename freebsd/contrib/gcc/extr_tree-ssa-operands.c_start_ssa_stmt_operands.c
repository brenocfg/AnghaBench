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

/* Variables and functions */
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_defs ; 
 int /*<<< orphan*/  build_uses ; 
 int /*<<< orphan*/  build_v_may_defs ; 
 int /*<<< orphan*/  build_v_must_defs ; 
 int /*<<< orphan*/  build_vuses ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static inline void
start_ssa_stmt_operands (void)
{
  gcc_assert (VEC_length (tree, build_defs) == 0);
  gcc_assert (VEC_length (tree, build_uses) == 0);
  gcc_assert (VEC_length (tree, build_vuses) == 0);
  gcc_assert (VEC_length (tree, build_v_may_defs) == 0);
  gcc_assert (VEC_length (tree, build_v_must_defs) == 0);
}