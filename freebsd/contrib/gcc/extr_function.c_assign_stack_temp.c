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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  assign_stack_temp_for_type (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

rtx
assign_stack_temp (enum machine_mode mode, HOST_WIDE_INT size, int keep)
{
  return assign_stack_temp_for_type (mode, size, keep, NULL_TREE);
}