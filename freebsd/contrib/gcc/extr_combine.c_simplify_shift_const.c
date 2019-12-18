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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ gen_lowpart (int,scalar_t__) ; 
 scalar_t__ simplify_gen_binary (int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_shift_const_1 (int,int,scalar_t__,int) ; 

__attribute__((used)) static rtx
simplify_shift_const (rtx x, enum rtx_code code, enum machine_mode result_mode,
		      rtx varop, int count)
{
  rtx tem = simplify_shift_const_1 (code, result_mode, varop, count);
  if (tem)
    return tem;

  if (!x)
    x = simplify_gen_binary (code, GET_MODE (varop), varop, GEN_INT (count));
  if (GET_MODE (x) != result_mode)
    x = gen_lowpart (result_mode, x);
  return x;
}