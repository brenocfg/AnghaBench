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
typedef  scalar_t__ uint ;

/* Variables and functions */
 scalar_t__ AY ; 
 scalar_t__ MAKE_INT_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ MASK_OUT_ABOVE_32 (scalar_t__) ; 
 int /*<<< orphan*/  OPER_I_16 () ; 
 scalar_t__* REG_A ; 
 int /*<<< orphan*/  m68ki_push_32 (scalar_t__) ; 

__attribute__((used)) static void m68k_op_link_16(void)
{
  uint* r_dst = &AY;

  m68ki_push_32(*r_dst);
  *r_dst = REG_A[7];
  REG_A[7] = MASK_OUT_ABOVE_32(REG_A[7] + MAKE_INT_16(OPER_I_16()));
}