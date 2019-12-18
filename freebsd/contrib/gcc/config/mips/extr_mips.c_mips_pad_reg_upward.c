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
 int /*<<< orphan*/  BYTES_BIG_ENDIAN ; 
 int FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ MODE_FLOAT ; 
 int mips_pad_arg_upward (int,scalar_t__) ; 

bool
mips_pad_reg_upward (enum machine_mode mode, tree type)
{
  /* No shifting is required for floating-point arguments.  */
  if (type != 0 ? FLOAT_TYPE_P (type) : GET_MODE_CLASS (mode) == MODE_FLOAT)
    return !BYTES_BIG_ENDIAN;

  /* Otherwise, apply the same padding to register arguments as we do
     to stack arguments.  */
  return mips_pad_arg_upward (mode, type);
}