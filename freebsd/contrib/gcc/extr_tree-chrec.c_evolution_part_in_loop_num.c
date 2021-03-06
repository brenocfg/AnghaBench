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
 int /*<<< orphan*/  chrec_component_in_loop_num (int /*<<< orphan*/ ,unsigned int,int) ; 

tree 
evolution_part_in_loop_num (tree chrec, 
			    unsigned loop_num)
{
  return chrec_component_in_loop_num (chrec, loop_num, true);
}