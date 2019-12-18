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
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_C_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 

__attribute__((used)) static tree
next_initializable_field (tree field)
{
  while (field
	 && (TREE_CODE (field) != FIELD_DECL
	     || (DECL_C_BIT_FIELD (field) && !DECL_NAME (field))
	     || DECL_ARTIFICIAL (field)))
    field = TREE_CHAIN (field);

  return field;
}