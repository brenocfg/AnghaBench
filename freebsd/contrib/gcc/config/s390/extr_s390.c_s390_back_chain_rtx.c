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
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ STACK_POINTER_OFFSET ; 
 int /*<<< orphan*/  TARGET_BACKCHAIN ; 
 scalar_t__ TARGET_PACKED_STACK ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

rtx
s390_back_chain_rtx (void)
{
  rtx chain;

  gcc_assert (TARGET_BACKCHAIN);

  if (TARGET_PACKED_STACK)
    chain = plus_constant (stack_pointer_rtx,
			   STACK_POINTER_OFFSET - UNITS_PER_WORD);
  else
    chain = stack_pointer_rtx;

  chain = gen_rtx_MEM (Pmode, chain);
  return chain;
}