#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  X_add_symbol; scalar_t__ X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_LOAD_INSN ; 
 int /*<<< orphan*/  BFD_RELOC_MIPS_GOT16 ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_gp_register ; 
 int /*<<< orphan*/  relax_end () ; 
 int /*<<< orphan*/  relax_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_switch () ; 

__attribute__((used)) static void
load_got_offset (int dest, expressionS *local)
{
  expressionS global;

  global = *local;
  global.X_add_number = 0;

  relax_start (local->X_add_symbol);
  macro_build (&global, ADDRESS_LOAD_INSN, "t,o(b)", dest,
	       BFD_RELOC_MIPS_GOT16, mips_gp_register);
  relax_switch ();
  macro_build (local, ADDRESS_LOAD_INSN, "t,o(b)", dest,
	       BFD_RELOC_MIPS_GOT16, mips_gp_register);
  relax_end ();
}