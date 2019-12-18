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
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  global_namespace ; 
 scalar_t__ namespace_binding (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_typename_at_global_scope (tree id)
{
  tree global_value = namespace_binding (id, global_namespace);

  return global_value && TREE_CODE (global_value) == TYPE_DECL;
}