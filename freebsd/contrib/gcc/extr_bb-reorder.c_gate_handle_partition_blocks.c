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
 int /*<<< orphan*/  DECL_ONE_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 
 int /*<<< orphan*/  user_defined_section_attribute ; 

__attribute__((used)) static bool
gate_handle_partition_blocks (void)
{
  /* The optimization to partition hot/cold basic blocks into separate
     sections of the .o file does not work well with linkonce or with
     user defined section attributes.  Don't call it if either case
     arises.  */

  return (flag_reorder_blocks_and_partition
	  && !DECL_ONE_ONLY (current_function_decl)
	  && !user_defined_section_attribute);
}