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
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_promotes_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
promoted_arithmetic_type_p (tree type)
{
  /* [over.built]

     In this section, the term promoted integral type is used to refer
     to those integral types which are preserved by integral promotion
     (including e.g.  int and long but excluding e.g.  char).
     Similarly, the term promoted arithmetic type refers to promoted
     integral types plus floating types.  */
  return ((INTEGRAL_TYPE_P (type)
	   && same_type_p (type_promotes_to (type), type))
	  || TREE_CODE (type) == REAL_TYPE);
}