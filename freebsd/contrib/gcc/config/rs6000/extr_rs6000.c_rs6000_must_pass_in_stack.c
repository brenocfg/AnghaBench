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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ABI_AIX ; 
 scalar_t__ DEFAULT_ABI ; 
 scalar_t__ TARGET_64BIT ; 
 int must_pass_in_stack_var_size (int,int /*<<< orphan*/ ) ; 
 int must_pass_in_stack_var_size_or_pad (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
rs6000_must_pass_in_stack (enum machine_mode mode, tree type)
{
  if (DEFAULT_ABI == ABI_AIX || TARGET_64BIT)
    return must_pass_in_stack_var_size (mode, type);
  else
    return must_pass_in_stack_var_size_or_pad (mode, type);
}