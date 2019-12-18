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
 int /*<<< orphan*/  CASE_LOW (int /*<<< orphan*/ ) ; 
 int tree_int_cst_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_case_labels (const void *p1, const void *p2)
{
  tree case1 = *(tree *)p1;
  tree case2 = *(tree *)p2;

  return tree_int_cst_compare (CASE_LOW (case1), CASE_LOW (case2));
}