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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ARG_POINTER_CFA_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ FRAME_POINTER_CFA_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 scalar_t__ plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_equiv_address_nv (scalar_t__,scalar_t__) ; 
 scalar_t__ replace_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ simplify_rtx (scalar_t__) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static rtx
adjust_stack_reference (rtx mem, HOST_WIDE_INT adjustment)
{
  rtx addr, cfa, tmp;

#ifdef FRAME_POINTER_CFA_OFFSET
  adjustment -= FRAME_POINTER_CFA_OFFSET (current_function_decl);
  cfa = plus_constant (frame_pointer_rtx, adjustment);
#else
  adjustment -= ARG_POINTER_CFA_OFFSET (current_function_decl);
  cfa = plus_constant (arg_pointer_rtx, adjustment);
#endif

  addr = replace_rtx (copy_rtx (XEXP (mem, 0)), stack_pointer_rtx, cfa);
  tmp = simplify_rtx (addr);
  if (tmp)
    addr = tmp;

  return replace_equiv_address_nv (mem, addr);
}