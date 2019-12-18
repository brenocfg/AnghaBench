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
#define  ABI_AIX 130 
#define  ABI_DARWIN 129 
#define  ABI_V4 128 
 int DEFAULT_ABI ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_DEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_PLUS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_32BIT ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rs6000_trampoline_size () ; 

void
rs6000_initialize_trampoline (rtx addr, rtx fnaddr, rtx cxt)
{
  int regsize = (TARGET_32BIT) ? 4 : 8;
  rtx ctx_reg = force_reg (Pmode, cxt);

  switch (DEFAULT_ABI)
    {
    default:
      gcc_unreachable ();

/* Macros to shorten the code expansions below.  */
#define MEM_DEREF(addr) gen_rtx_MEM (Pmode, memory_address (Pmode, addr))
#define MEM_PLUS(addr,offset) \
  gen_rtx_MEM (Pmode, memory_address (Pmode, plus_constant (addr, offset)))

    /* Under AIX, just build the 3 word function descriptor */
    case ABI_AIX:
      {
	rtx fn_reg = gen_reg_rtx (Pmode);
	rtx toc_reg = gen_reg_rtx (Pmode);
	emit_move_insn (fn_reg, MEM_DEREF (fnaddr));
	emit_move_insn (toc_reg, MEM_PLUS (fnaddr, regsize));
	emit_move_insn (MEM_DEREF (addr), fn_reg);
	emit_move_insn (MEM_PLUS (addr, regsize), toc_reg);
	emit_move_insn (MEM_PLUS (addr, 2*regsize), ctx_reg);
      }
      break;

    /* Under V.4/eabi/darwin, __trampoline_setup does the real work.  */
    case ABI_DARWIN:
    case ABI_V4:
      emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__trampoline_setup"),
			 FALSE, VOIDmode, 4,
			 addr, Pmode,
			 GEN_INT (rs6000_trampoline_size ()), SImode,
			 fnaddr, Pmode,
			 ctx_reg, Pmode);
      break;
    }

  return;
}