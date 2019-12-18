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
 int cp_type_quals (int /*<<< orphan*/ ) ; 

int
comp_cv_qualification (tree type1, tree type2)
{
  int q1 = cp_type_quals (type1);
  int q2 = cp_type_quals (type2);

  if (q1 == q2)
    return 0;

  if ((q1 & q2) == q2)
    return 1;
  else if ((q1 & q2) == q1)
    return -1;

  return 0;
}