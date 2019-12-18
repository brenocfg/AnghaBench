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
 scalar_t__ ABI_EABI ; 
 scalar_t__ ABI_O64 ; 
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int /*<<< orphan*/  BYTES_BIG_ENDIAN ; 
 int FLOAT_TYPE_P (scalar_t__) ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ MODE_FLOAT ; 
 scalar_t__ MODE_INT ; 
 int PARM_BOUNDARY ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 int int_size_in_bytes (scalar_t__) ; 
 scalar_t__ mips_abi ; 

bool
mips_pad_arg_upward (enum machine_mode mode, tree type)
{
  /* On little-endian targets, the first byte of every stack argument
     is passed in the first byte of the stack slot.  */
  if (!BYTES_BIG_ENDIAN)
    return true;

  /* Otherwise, integral types are padded downward: the last byte of a
     stack argument is passed in the last byte of the stack slot.  */
  if (type != 0
      ? INTEGRAL_TYPE_P (type) || POINTER_TYPE_P (type)
      : GET_MODE_CLASS (mode) == MODE_INT)
    return false;

  /* Big-endian o64 pads floating-point arguments downward.  */
  if (mips_abi == ABI_O64)
    if (type != 0 ? FLOAT_TYPE_P (type) : GET_MODE_CLASS (mode) == MODE_FLOAT)
      return false;

  /* Other types are padded upward for o32, o64, n32 and n64.  */
  if (mips_abi != ABI_EABI)
    return true;

  /* Arguments smaller than a stack slot are padded downward.  */
  if (mode != BLKmode)
    return (GET_MODE_BITSIZE (mode) >= PARM_BOUNDARY);
  else
    return (int_size_in_bytes (type) >= (PARM_BOUNDARY / BITS_PER_UNIT));
}