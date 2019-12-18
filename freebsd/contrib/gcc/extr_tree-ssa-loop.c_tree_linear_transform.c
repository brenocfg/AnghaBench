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

/* Variables and functions */
 int /*<<< orphan*/  current_loops ; 
 int /*<<< orphan*/  linear_transform_loops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tree_linear_transform (void)
{
  if (!current_loops)
    return 0;

  linear_transform_loops (current_loops);
  return 0;
}