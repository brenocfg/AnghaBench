#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_ADDI_INSN ; 
 int /*<<< orphan*/  ADDRESS_ADD_INSN ; 
 int BFD_RELOC_LO16 ; 
 int /*<<< orphan*/  HAVE_64BIT_ADDRESSES ; 
 int /*<<< orphan*/  O_constant ; 
 int /*<<< orphan*/  load_register (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  macro_build_lui (TYPE_1__*,int) ; 
 int mips_optimize ; 
 int /*<<< orphan*/  relax_end () ; 
 int /*<<< orphan*/  relax_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relax_switch () ; 

__attribute__((used)) static void
add_got_offset_hilo (int dest, expressionS *local, int tmp)
{
  expressionS global;
  int hold_mips_optimize;

  global.X_op = O_constant;
  global.X_op_symbol = NULL;
  global.X_add_symbol = NULL;
  global.X_add_number = local->X_add_number;

  relax_start (local->X_add_symbol);
  load_register (tmp, &global, HAVE_64BIT_ADDRESSES);
  relax_switch ();
  /* Set mips_optimize around the lui instruction to avoid
     inserting an unnecessary nop after the lw.  */
  hold_mips_optimize = mips_optimize;
  mips_optimize = 2;
  macro_build_lui (&global, tmp);
  mips_optimize = hold_mips_optimize;
  macro_build (local, ADDRESS_ADDI_INSN, "t,r,j", tmp, tmp, BFD_RELOC_LO16);
  relax_end ();

  macro_build (NULL, ADDRESS_ADD_INSN, "d,v,t", dest, dest, tmp);
}