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
 scalar_t__ current_namespace ; 
 scalar_t__ current_scope () ; 
 int /*<<< orphan*/  push_inner_scope_r (scalar_t__,scalar_t__) ; 

tree
push_inner_scope (tree inner)
{
  tree outer = current_scope ();
  if (!outer)
    outer = current_namespace;

  push_inner_scope_r (outer, inner);
  return outer;
}