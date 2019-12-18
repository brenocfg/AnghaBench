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

/* Variables and functions */
 scalar_t__ MEM_IN_STRUCT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_SCALAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  flag_strict_aliasing ; 

__attribute__((used)) static rtx
fixed_scalar_and_varying_struct_p (rtx mem1, rtx mem2, rtx mem1_addr,
				   rtx mem2_addr,
				   int (*varies_p) (rtx, int))
{
  if (! flag_strict_aliasing)
    return NULL_RTX;

  if (MEM_SCALAR_P (mem1) && MEM_IN_STRUCT_P (mem2)
      && !varies_p (mem1_addr, 1) && varies_p (mem2_addr, 1))
    /* MEM1 is a scalar at a fixed address; MEM2 is a struct at a
       varying address.  */
    return mem1;

  if (MEM_IN_STRUCT_P (mem1) && MEM_SCALAR_P (mem2)
      && varies_p (mem1_addr, 1) && !varies_p (mem2_addr, 1))
    /* MEM2 is a scalar at a fixed address; MEM1 is a struct at a
       varying address.  */
    return mem2;

  return NULL_RTX;
}