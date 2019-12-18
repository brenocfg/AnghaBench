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
 int reference_related_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
objcp_reference_related_p (tree t1, tree t2)
{
  return reference_related_p (t1, t2);
}