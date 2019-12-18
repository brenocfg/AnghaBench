#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  (* guard_mask_bit ) () ;} ;
struct TYPE_4__ {TYPE_1__ cxx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static tree
get_guard_bits (tree guard)
{
  if (!targetm.cxx.guard_mask_bit ())
    {
      /* We only set the first byte of the guard, in order to leave room
	 for a mutex in the high-order bits.  */
      guard = build1 (ADDR_EXPR,
		      build_pointer_type (TREE_TYPE (guard)),
		      guard);
      guard = build1 (NOP_EXPR,
		      build_pointer_type (char_type_node),
		      guard);
      guard = build1 (INDIRECT_REF, char_type_node, guard);
    }

  return guard;
}