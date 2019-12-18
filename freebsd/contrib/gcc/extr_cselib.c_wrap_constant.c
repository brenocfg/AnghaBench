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

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
wrap_constant (enum machine_mode mode, rtx x)
{
  if (GET_CODE (x) != CONST_INT
      && (GET_CODE (x) != CONST_DOUBLE || GET_MODE (x) != VOIDmode))
    return x;
  gcc_assert (mode != VOIDmode);
  return gen_rtx_CONST (mode, x);
}