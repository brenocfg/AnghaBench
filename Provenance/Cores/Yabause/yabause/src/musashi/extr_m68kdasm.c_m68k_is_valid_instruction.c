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

/* Variables and functions */
#define  M68K_CPU_TYPE_68000 132 
#define  M68K_CPU_TYPE_68010 131 
#define  M68K_CPU_TYPE_68020 130 
#define  M68K_CPU_TYPE_68030 129 
#define  M68K_CPU_TYPE_68EC020 128 
 int /*<<< orphan*/  build_opcode_table () ; 
 scalar_t__ d68000_illegal ; 
 scalar_t__ d68010_bkpt ; 
 scalar_t__ d68010_move_fr_ccr ; 
 scalar_t__ d68010_movec ; 
 scalar_t__ d68010_moves_16 ; 
 scalar_t__ d68010_moves_32 ; 
 scalar_t__ d68010_moves_8 ; 
 scalar_t__ d68010_rtd ; 
 scalar_t__ d68020_bcc_32 ; 
 scalar_t__ d68020_bfchg ; 
 scalar_t__ d68020_bfclr ; 
 scalar_t__ d68020_bfexts ; 
 scalar_t__ d68020_bfextu ; 
 scalar_t__ d68020_bfffo ; 
 scalar_t__ d68020_bfins ; 
 scalar_t__ d68020_bfset ; 
 scalar_t__ d68020_bftst ; 
 scalar_t__ d68020_bra_32 ; 
 scalar_t__ d68020_bsr_32 ; 
 scalar_t__ d68020_callm ; 
 scalar_t__ d68020_cas2_16 ; 
 scalar_t__ d68020_cas2_32 ; 
 scalar_t__ d68020_cas_16 ; 
 scalar_t__ d68020_cas_32 ; 
 scalar_t__ d68020_cas_8 ; 
 scalar_t__ d68020_chk2_cmp2_16 ; 
 scalar_t__ d68020_chk2_cmp2_32 ; 
 scalar_t__ d68020_chk2_cmp2_8 ; 
 scalar_t__ d68020_chk_32 ; 
 scalar_t__ d68020_cmpi_pcdi_16 ; 
 scalar_t__ d68020_cmpi_pcdi_32 ; 
 scalar_t__ d68020_cmpi_pcdi_8 ; 
 scalar_t__ d68020_cmpi_pcix_16 ; 
 scalar_t__ d68020_cmpi_pcix_32 ; 
 scalar_t__ d68020_cmpi_pcix_8 ; 
 scalar_t__ d68020_cpbcc_16 ; 
 scalar_t__ d68020_cpbcc_32 ; 
 scalar_t__ d68020_cpdbcc ; 
 scalar_t__ d68020_cpgen ; 
 scalar_t__ d68020_cprestore ; 
 scalar_t__ d68020_cpsave ; 
 scalar_t__ d68020_cpscc ; 
 scalar_t__ d68020_cptrapcc_0 ; 
 scalar_t__ d68020_cptrapcc_16 ; 
 scalar_t__ d68020_cptrapcc_32 ; 
 scalar_t__ d68020_divl ; 
 scalar_t__ d68020_extb_32 ; 
 scalar_t__ d68020_link_32 ; 
 scalar_t__ d68020_mull ; 
 scalar_t__ d68020_pack_mm ; 
 scalar_t__ d68020_pack_rr ; 
 scalar_t__ d68020_rtm ; 
 scalar_t__ d68020_trapcc_0 ; 
 scalar_t__ d68020_trapcc_16 ; 
 scalar_t__ d68020_trapcc_32 ; 
 scalar_t__ d68020_tst_a_16 ; 
 scalar_t__ d68020_tst_a_32 ; 
 scalar_t__ d68020_tst_i_16 ; 
 scalar_t__ d68020_tst_i_32 ; 
 scalar_t__ d68020_tst_i_8 ; 
 scalar_t__ d68020_tst_pcdi_16 ; 
 scalar_t__ d68020_tst_pcdi_32 ; 
 scalar_t__ d68020_tst_pcdi_8 ; 
 scalar_t__ d68020_tst_pcix_16 ; 
 scalar_t__ d68020_tst_pcix_32 ; 
 scalar_t__ d68020_tst_pcix_8 ; 
 scalar_t__ d68020_unpk_mm ; 
 scalar_t__ d68020_unpk_rr ; 
 scalar_t__ d68040_cinv ; 
 scalar_t__ d68040_cpush ; 
 scalar_t__ d68040_move16_ai_al ; 
 scalar_t__ d68040_move16_al_ai ; 
 scalar_t__ d68040_move16_al_pi ; 
 scalar_t__ d68040_move16_pi_al ; 
 scalar_t__ d68040_move16_pi_pi ; 
 int g_initialized ; 
 scalar_t__* g_instruction_table ; 

unsigned int m68k_is_valid_instruction(unsigned int instruction, unsigned int cpu_type)
{
	if(!g_initialized)
	{
		build_opcode_table();
		g_initialized = 1;
	}

	instruction &= 0xffff;
	if(g_instruction_table[instruction] == d68000_illegal)
		return 0;

	switch(cpu_type)
	{
		case M68K_CPU_TYPE_68000:
			if(g_instruction_table[instruction] == d68010_bkpt)
				return 0;
			if(g_instruction_table[instruction] == d68010_move_fr_ccr)
				return 0;
			if(g_instruction_table[instruction] == d68010_movec)
				return 0;
			if(g_instruction_table[instruction] == d68010_moves_8)
				return 0;
			if(g_instruction_table[instruction] == d68010_moves_16)
				return 0;
			if(g_instruction_table[instruction] == d68010_moves_32)
				return 0;
			if(g_instruction_table[instruction] == d68010_rtd)
				return 0;
		case M68K_CPU_TYPE_68010:
			if(g_instruction_table[instruction] == d68020_bcc_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfchg)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfclr)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfexts)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfextu)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfffo)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfins)
				return 0;
			if(g_instruction_table[instruction] == d68020_bfset)
				return 0;
			if(g_instruction_table[instruction] == d68020_bftst)
				return 0;
			if(g_instruction_table[instruction] == d68020_bra_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_bsr_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_callm)
				return 0;
			if(g_instruction_table[instruction] == d68020_cas_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_cas_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cas_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_cas2_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cas2_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_chk_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_chk2_cmp2_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_chk2_cmp2_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_chk2_cmp2_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcdi_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcix_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcdi_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcix_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcdi_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_cmpi_pcix_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpbcc_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpbcc_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpdbcc)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpgen)
				return 0;
			if(g_instruction_table[instruction] == d68020_cprestore)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpsave)
				return 0;
			if(g_instruction_table[instruction] == d68020_cpscc)
				return 0;
			if(g_instruction_table[instruction] == d68020_cptrapcc_0)
				return 0;
			if(g_instruction_table[instruction] == d68020_cptrapcc_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_cptrapcc_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_divl)
				return 0;
			if(g_instruction_table[instruction] == d68020_extb_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_link_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_mull)
				return 0;
			if(g_instruction_table[instruction] == d68020_pack_rr)
				return 0;
			if(g_instruction_table[instruction] == d68020_pack_mm)
				return 0;
			if(g_instruction_table[instruction] == d68020_rtm)
				return 0;
			if(g_instruction_table[instruction] == d68020_trapcc_0)
				return 0;
			if(g_instruction_table[instruction] == d68020_trapcc_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_trapcc_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcdi_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcix_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_i_8)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_a_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcdi_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcix_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_i_16)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_a_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcdi_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_pcix_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_tst_i_32)
				return 0;
			if(g_instruction_table[instruction] == d68020_unpk_rr)
				return 0;
			if(g_instruction_table[instruction] == d68020_unpk_mm)
				return 0;
		case M68K_CPU_TYPE_68EC020:
		case M68K_CPU_TYPE_68020:
		case M68K_CPU_TYPE_68030:
			if(g_instruction_table[instruction] == d68040_cinv)
				return 0;
			if(g_instruction_table[instruction] == d68040_cpush)
				return 0;
			if(g_instruction_table[instruction] == d68040_move16_pi_pi)
				return 0;
			if(g_instruction_table[instruction] == d68040_move16_pi_al)
				return 0;
			if(g_instruction_table[instruction] == d68040_move16_al_pi)
				return 0;
			if(g_instruction_table[instruction] == d68040_move16_ai_al)
				return 0;
			if(g_instruction_table[instruction] == d68040_move16_al_ai)
				return 0;
	}
	if(cpu_type != M68K_CPU_TYPE_68020 && cpu_type != M68K_CPU_TYPE_68EC020 &&
	  (g_instruction_table[instruction] == d68020_callm ||
	  g_instruction_table[instruction] == d68020_rtm))
		return 0;

	return 1;
}