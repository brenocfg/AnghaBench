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

/* Variables and functions */
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  reg_mentioned_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
unmentioned_reg_p_1 (rtx *loc, void *expr)
{
  rtx x = *loc;

  if (x != NULL_RTX
      && (REG_P (x) || MEM_P (x))
      && ! reg_mentioned_p (x, (rtx) expr))
    return 1;
  return 0;
}