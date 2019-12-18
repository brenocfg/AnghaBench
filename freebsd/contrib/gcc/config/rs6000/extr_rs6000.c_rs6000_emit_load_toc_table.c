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
 scalar_t__ ABI_AIX ; 
 scalar_t__ ABI_V4 ; 
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int) ; 
 scalar_t__ DEFAULT_ABI ; 
 int /*<<< orphan*/  LINK_REGISTER_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RS6000_PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ TARGET_32BIT ; 
 int /*<<< orphan*/  TARGET_AIX ; 
 scalar_t__ TARGET_ELF ; 
 scalar_t__ TARGET_MINIMAL_TOC ; 
 scalar_t__ TARGET_SECURE_PLT ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int flag_pic ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_elf_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_elf_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_aix_di (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_aix_si (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_PIC_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_PIC_1b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_PIC_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_PIC_3b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_PIC_3c (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_toc_v4_pic_si (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggc_strdup (char*) ; 
 int /*<<< orphan*/  rs6000_got_sym () ; 
 int /*<<< orphan*/  rs6000_maybe_dead (int /*<<< orphan*/ ) ; 
 int rs6000_pic_labelno ; 
 int /*<<< orphan*/  toc_label_name ; 

void
rs6000_emit_load_toc_table (int fromprolog)
{
  rtx dest, insn;
  dest = gen_rtx_REG (Pmode, RS6000_PIC_OFFSET_TABLE_REGNUM);

  if (TARGET_ELF && TARGET_SECURE_PLT && DEFAULT_ABI != ABI_AIX && flag_pic)
    {
      char buf[30];
      rtx lab, tmp1, tmp2, got, tempLR;

      ASM_GENERATE_INTERNAL_LABEL (buf, "LCF", rs6000_pic_labelno);
      lab = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (buf));
      if (flag_pic == 2)
	got = gen_rtx_SYMBOL_REF (Pmode, toc_label_name);
      else
	got = rs6000_got_sym ();
      tmp1 = tmp2 = dest;
      if (!fromprolog)
	{
	  tmp1 = gen_reg_rtx (Pmode);
	  tmp2 = gen_reg_rtx (Pmode);
	}
      tempLR = (fromprolog
		? gen_rtx_REG (Pmode, LINK_REGISTER_REGNUM)
		: gen_reg_rtx (Pmode));
      insn = emit_insn (gen_load_toc_v4_PIC_1 (tempLR, lab));
      if (fromprolog)
	rs6000_maybe_dead (insn);
      insn = emit_move_insn (tmp1, tempLR);
      if (fromprolog)
	rs6000_maybe_dead (insn);
      insn = emit_insn (gen_load_toc_v4_PIC_3b (tmp2, tmp1, got, lab));
      if (fromprolog)
	rs6000_maybe_dead (insn);
      insn = emit_insn (gen_load_toc_v4_PIC_3c (dest, tmp2, got, lab));
      if (fromprolog)
	rs6000_maybe_dead (insn);
    }
  else if (TARGET_ELF && DEFAULT_ABI == ABI_V4 && flag_pic == 1)
    {
      rtx tempLR = (fromprolog
		    ? gen_rtx_REG (Pmode, LINK_REGISTER_REGNUM)
		    : gen_reg_rtx (Pmode));

      insn = emit_insn (gen_load_toc_v4_pic_si (tempLR));
      if (fromprolog)
	rs6000_maybe_dead (insn);
      insn = emit_move_insn (dest, tempLR);
      if (fromprolog)
	rs6000_maybe_dead (insn);
    }
  else if (TARGET_ELF && DEFAULT_ABI != ABI_AIX && flag_pic == 2)
    {
      char buf[30];
      rtx tempLR = (fromprolog
		    ? gen_rtx_REG (Pmode, LINK_REGISTER_REGNUM)
		    : gen_reg_rtx (Pmode));
      rtx temp0 = (fromprolog
		   ? gen_rtx_REG (Pmode, 0)
		   : gen_reg_rtx (Pmode));

      if (fromprolog)
	{
	  rtx symF, symL;

	  ASM_GENERATE_INTERNAL_LABEL (buf, "LCF", rs6000_pic_labelno);
	  symF = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (buf));

	  ASM_GENERATE_INTERNAL_LABEL (buf, "LCL", rs6000_pic_labelno);
	  symL = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (buf));

	  rs6000_maybe_dead (emit_insn (gen_load_toc_v4_PIC_1 (tempLR,
							       symF)));
	  rs6000_maybe_dead (emit_move_insn (dest, tempLR));
	  rs6000_maybe_dead (emit_insn (gen_load_toc_v4_PIC_2 (temp0, dest,
							       symL,
							       symF)));
	}
      else
	{
	  rtx tocsym;

	  tocsym = gen_rtx_SYMBOL_REF (Pmode, toc_label_name);
	  emit_insn (gen_load_toc_v4_PIC_1b (tempLR, tocsym));
	  emit_move_insn (dest, tempLR);
	  emit_move_insn (temp0, gen_rtx_MEM (Pmode, dest));
	}
      insn = emit_insn (gen_addsi3 (dest, temp0, dest));
      if (fromprolog)
	rs6000_maybe_dead (insn);
    }
  else if (TARGET_ELF && !TARGET_AIX && flag_pic == 0 && TARGET_MINIMAL_TOC)
    {
      /* This is for AIX code running in non-PIC ELF32.  */
      char buf[30];
      rtx realsym;
      ASM_GENERATE_INTERNAL_LABEL (buf, "LCTOC", 1);
      realsym = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (buf));

      insn = emit_insn (gen_elf_high (dest, realsym));
      if (fromprolog)
	rs6000_maybe_dead (insn);
      insn = emit_insn (gen_elf_low (dest, dest, realsym));
      if (fromprolog)
	rs6000_maybe_dead (insn);
    }
  else
    {
      gcc_assert (DEFAULT_ABI == ABI_AIX);

      if (TARGET_32BIT)
	insn = emit_insn (gen_load_toc_aix_si (dest));
      else
	insn = emit_insn (gen_load_toc_aix_di (dest));
      if (fromprolog)
	rs6000_maybe_dead (insn);
    }
}