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
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RETURN_ADDR_OFFSET ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 

rtx
expand_builtin_frob_return_addr (tree addr_tree)
{
  rtx addr = expand_expr (addr_tree, NULL_RTX, ptr_mode, 0);

  addr = convert_memory_address (Pmode, addr);

#ifdef RETURN_ADDR_OFFSET
  addr = force_reg (Pmode, addr);
  addr = plus_constant (addr, -RETURN_ADDR_OFFSET);
#endif

  return addr;
}