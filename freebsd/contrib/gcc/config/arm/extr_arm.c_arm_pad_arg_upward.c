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
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ DEFAULT_FUNCTION_ARG_PADDING (int,scalar_t__) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_AAPCS_BASED ; 
 scalar_t__ upward ; 

bool
arm_pad_arg_upward (enum machine_mode mode, tree type)
{
  if (!TARGET_AAPCS_BASED)
    return DEFAULT_FUNCTION_ARG_PADDING(mode, type) == upward;

  if (type && BYTES_BIG_ENDIAN && INTEGRAL_TYPE_P (type))
    return false;

  return true;
}