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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 TYPE_1__* outer_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

tree
innermost_non_namespace_value (tree name)
{
  cxx_binding *binding;
  binding = outer_binding (name, /*binding=*/NULL, /*class_p=*/true);
  return binding ? binding->value : NULL_TREE;
}