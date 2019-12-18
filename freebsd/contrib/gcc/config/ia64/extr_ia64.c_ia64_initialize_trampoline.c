#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  (* globalize_label ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TARGET_GNU_AS ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ targetm ; 

void
ia64_initialize_trampoline (rtx addr, rtx fnaddr, rtx static_chain)
{
  rtx addr_reg, eight = GEN_INT (8);

  /* The Intel assembler requires that the global __ia64_trampoline symbol
     be declared explicitly */
  if (!TARGET_GNU_AS)
    {
      static bool declared_ia64_trampoline = false;

      if (!declared_ia64_trampoline)
	{
	  declared_ia64_trampoline = true;
	  (*targetm.asm_out.globalize_label) (asm_out_file,
					      "__ia64_trampoline");
	}
    }

  /* Make sure addresses are Pmode even if we are in ILP32 mode. */
  addr = convert_memory_address (Pmode, addr);
  fnaddr = convert_memory_address (Pmode, fnaddr);
  static_chain = convert_memory_address (Pmode, static_chain);

  /* Load up our iterator.  */
  addr_reg = gen_reg_rtx (Pmode);
  emit_move_insn (addr_reg, addr);

  /* The first two words are the fake descriptor:
     __ia64_trampoline, ADDR+16.  */
  emit_move_insn (gen_rtx_MEM (Pmode, addr_reg),
		  gen_rtx_SYMBOL_REF (Pmode, "__ia64_trampoline"));
  emit_insn (gen_adddi3 (addr_reg, addr_reg, eight));

  emit_move_insn (gen_rtx_MEM (Pmode, addr_reg),
		  copy_to_reg (plus_constant (addr, 16)));
  emit_insn (gen_adddi3 (addr_reg, addr_reg, eight));

  /* The third word is the target descriptor.  */
  emit_move_insn (gen_rtx_MEM (Pmode, addr_reg), fnaddr);
  emit_insn (gen_adddi3 (addr_reg, addr_reg, eight));

  /* The fourth word is the static chain.  */
  emit_move_insn (gen_rtx_MEM (Pmode, addr_reg), static_chain);
}