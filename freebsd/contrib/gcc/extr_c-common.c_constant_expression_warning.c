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
 scalar_t__ COMPLEX_CST ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ VECTOR_CST ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ warn_overflow ; 

void
constant_expression_warning (tree value)
{
  if ((TREE_CODE (value) == INTEGER_CST || TREE_CODE (value) == REAL_CST
       || TREE_CODE (value) == VECTOR_CST
       || TREE_CODE (value) == COMPLEX_CST)
      && TREE_CONSTANT_OVERFLOW (value)
      && warn_overflow
      && pedantic)
    pedwarn ("overflow in constant expression");
}