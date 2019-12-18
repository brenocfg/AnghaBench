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
 int BRA_INSN (void (*) (),int) ; 
 void alignment_check () ; 
 void cache_flushing_handler () ; 
 void debug_trap () ; 
 void ei_handler () ; 
 int* eit_vector ; 
 void ill_trap () ; 
 void rie_handler () ; 
 scalar_t__ smp_call_function_interrupt ; 
 scalar_t__ smp_call_function_single_interrupt ; 
 scalar_t__ smp_flush_cache_all_interrupt ; 
 scalar_t__ smp_invalidate_interrupt ; 
 scalar_t__ smp_ipi_timer_interrupt ; 
 scalar_t__ smp_reschedule_interrupt ; 

__attribute__((used)) static void set_eit_vector_entries(void)
{
	extern void default_eit_handler(void);
	extern void system_call(void);
	extern void pie_handler(void);
	extern void ace_handler(void);
	extern void tme_handler(void);
	extern void _flush_cache_copyback_all(void);

	eit_vector[0] = 0xd0c00001; /* seth r0, 0x01 */
	eit_vector[1] = BRA_INSN(default_eit_handler, 1);
	eit_vector[4] = 0xd0c00010; /* seth r0, 0x10 */
	eit_vector[5] = BRA_INSN(default_eit_handler, 5);
	eit_vector[8] = BRA_INSN(rie_handler, 8);
	eit_vector[12] = BRA_INSN(alignment_check, 12);
	eit_vector[16] = BRA_INSN(ill_trap, 16);
	eit_vector[17] = BRA_INSN(debug_trap, 17);
	eit_vector[18] = BRA_INSN(system_call, 18);
	eit_vector[19] = BRA_INSN(ill_trap, 19);
	eit_vector[20] = BRA_INSN(ill_trap, 20);
	eit_vector[21] = BRA_INSN(ill_trap, 21);
	eit_vector[22] = BRA_INSN(ill_trap, 22);
	eit_vector[23] = BRA_INSN(ill_trap, 23);
	eit_vector[24] = BRA_INSN(ill_trap, 24);
	eit_vector[25] = BRA_INSN(ill_trap, 25);
	eit_vector[26] = BRA_INSN(ill_trap, 26);
	eit_vector[27] = BRA_INSN(ill_trap, 27);
	eit_vector[28] = BRA_INSN(cache_flushing_handler, 28);
	eit_vector[29] = BRA_INSN(ill_trap, 29);
	eit_vector[30] = BRA_INSN(ill_trap, 30);
	eit_vector[31] = BRA_INSN(ill_trap, 31);
	eit_vector[32] = BRA_INSN(ei_handler, 32);
	eit_vector[64] = BRA_INSN(pie_handler, 64);
#ifdef CONFIG_MMU
	eit_vector[68] = BRA_INSN(ace_handler, 68);
	eit_vector[72] = BRA_INSN(tme_handler, 72);
#endif /* CONFIG_MMU */
#ifdef CONFIG_SMP
	eit_vector[184] = (unsigned long)smp_reschedule_interrupt;
	eit_vector[185] = (unsigned long)smp_invalidate_interrupt;
	eit_vector[186] = (unsigned long)smp_call_function_interrupt;
	eit_vector[187] = (unsigned long)smp_ipi_timer_interrupt;
	eit_vector[188] = (unsigned long)smp_flush_cache_all_interrupt;
	eit_vector[189] = 0;	/* CPU_BOOT_IPI */
	eit_vector[190] = (unsigned long)smp_call_function_single_interrupt;
	eit_vector[191] = 0;
#endif
	_flush_cache_copyback_all();
}