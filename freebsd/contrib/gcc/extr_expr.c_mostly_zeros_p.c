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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  categorize_ctor_elements (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int count_type_elements (int /*<<< orphan*/ ,int) ; 
 int initializer_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mostly_zeros_p (tree exp)
{
  if (TREE_CODE (exp) == CONSTRUCTOR)

    {
      HOST_WIDE_INT nz_elts, count, elts;
      bool must_clear;

      categorize_ctor_elements (exp, &nz_elts, &count, &must_clear);
      if (must_clear)
	return 1;

      elts = count_type_elements (TREE_TYPE (exp), false);

      return nz_elts < elts / 4;
    }

  return initializer_zerop (exp);
}