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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/  global_namespace ; 
 int /*<<< orphan*/ * namespace_binding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
get_global_value_if_present (tree id, tree *decl)
{
  tree global_value = namespace_binding (id, global_namespace);
  if (global_value)
    *decl = global_value;
  return global_value != NULL;
}