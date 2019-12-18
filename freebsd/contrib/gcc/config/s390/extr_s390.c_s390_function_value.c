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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 int promote_mode (scalar_t__,int /*<<< orphan*/ ,int*,int) ; 

rtx
s390_function_value (tree type, enum machine_mode mode)
{
  if (type)
    {
      int unsignedp = TYPE_UNSIGNED (type);
      mode = promote_mode (type, TYPE_MODE (type), &unsignedp, 1);
    }

  gcc_assert (GET_MODE_CLASS (mode) == MODE_INT || SCALAR_FLOAT_MODE_P (mode));
  gcc_assert (GET_MODE_SIZE (mode) <= 8);

  if (TARGET_HARD_FLOAT && SCALAR_FLOAT_MODE_P (mode))
    return gen_rtx_REG (mode, 16);
  else
    return gen_rtx_REG (mode, 2);
}