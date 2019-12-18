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
 scalar_t__ DECL_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 

__attribute__((used)) static bool
zero_sized_field_decl (tree fdecl)
{
  if (TREE_CODE (fdecl) == FIELD_DECL && DECL_SIZE (fdecl) 
      && integer_zerop (DECL_SIZE (fdecl)))
    return true;
  return false;
}