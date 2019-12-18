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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  gen_load_multiple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_frame_alias_set () ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
restore_gprs (rtx base, int offset, int first, int last)
{
  rtx addr, insn;

  addr = plus_constant (base, offset);
  addr = gen_rtx_MEM (Pmode, addr);
  set_mem_alias_set (addr, get_frame_alias_set ());

  /* Special-case single register.  */
  if (first == last)
    {
      if (TARGET_64BIT)
        insn = gen_movdi (gen_rtx_REG (Pmode, first), addr);
      else
        insn = gen_movsi (gen_rtx_REG (Pmode, first), addr);

      return insn;
    }

  insn = gen_load_multiple (gen_rtx_REG (Pmode, first),
			    addr,
			    GEN_INT (last - first + 1));
  return insn;
}