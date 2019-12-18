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
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_mode_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_add_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_legitimize_tls_address (int /*<<< orphan*/ ) ; 
 scalar_t__* mips_split_p ; 
 int /*<<< orphan*/  mips_split_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_symbolic_address_p (int,int) ; 
 scalar_t__ mips_symbolic_constant_p (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mips_tls_operand_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_valid_base_register_p (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool
mips_legitimize_address (rtx *xloc, enum machine_mode mode)
{
  enum mips_symbol_type symbol_type;

  if (mips_tls_operand_p (*xloc))
    {
      *xloc = mips_legitimize_tls_address (*xloc);
      return true;
    }

  /* See if the address can split into a high part and a LO_SUM.  */
  if (mips_symbolic_constant_p (*xloc, &symbol_type)
      && mips_symbolic_address_p (symbol_type, mode)
      && mips_split_p[symbol_type])
    {
      *xloc = mips_split_symbol (0, *xloc);
      return true;
    }

  if (GET_CODE (*xloc) == PLUS && GET_CODE (XEXP (*xloc, 1)) == CONST_INT)
    {
      /* Handle REG + CONSTANT using mips_add_offset.  */
      rtx reg;

      reg = XEXP (*xloc, 0);
      if (!mips_valid_base_register_p (reg, mode, 0))
	reg = copy_to_mode_reg (Pmode, reg);
      *xloc = mips_add_offset (0, reg, INTVAL (XEXP (*xloc, 1)));
      return true;
    }

  return false;
}