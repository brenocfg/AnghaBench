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
 int /*<<< orphan*/  INSERT ; 
 void* build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_specializations ; 

__attribute__((used)) static void
register_local_specialization (tree spec, tree tmpl)
{
  void **slot;

  slot = htab_find_slot_with_hash (local_specializations, tmpl,
				   htab_hash_pointer (tmpl), INSERT);
  *slot = build_tree_list (spec, tmpl);
}