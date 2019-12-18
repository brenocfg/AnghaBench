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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_RETURN_ADDR ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ Pmode ; 
 int /*<<< orphan*/  RETURN_ADDR_OFFSET ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  convert_memory_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_mode (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_and (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
expand_builtin_extract_return_addr (tree addr_tree)
{
  rtx addr = expand_expr (addr_tree, NULL_RTX, Pmode, 0);

  if (GET_MODE (addr) != Pmode
      && GET_MODE (addr) != VOIDmode)
    {
#ifdef POINTERS_EXTEND_UNSIGNED
      addr = convert_memory_address (Pmode, addr);
#else
      addr = convert_to_mode (Pmode, addr, 0);
#endif
    }

  /* First mask out any unwanted bits.  */
#ifdef MASK_RETURN_ADDR
  expand_and (Pmode, addr, MASK_RETURN_ADDR, addr);
#endif

  /* Then adjust to find the real return address.  */
#if defined (RETURN_ADDR_OFFSET)
  addr = plus_constant (addr, RETURN_ADDR_OFFSET);
#endif

  return addr;
}