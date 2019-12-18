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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  m68k_set_bkpt_ack_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_cmpild_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_fc_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_instr_hook_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_int_ack_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_pc_changed_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_reset_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_rte_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_tas_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68ki_build_opcode_table () ; 

void m68k_init(void)
{
	static uint emulation_initialized = 0;

	/* The first call to this function initializes the opcode handler jump table */
	if(!emulation_initialized)
		{
		m68ki_build_opcode_table();
		emulation_initialized = 1;
	}

	m68k_set_int_ack_callback(NULL);
	m68k_set_bkpt_ack_callback(NULL);
	m68k_set_reset_instr_callback(NULL);
	m68k_set_cmpild_instr_callback(NULL);
	m68k_set_rte_instr_callback(NULL);
	m68k_set_tas_instr_callback(NULL);
	m68k_set_pc_changed_callback(NULL);
	m68k_set_fc_callback(NULL);
	m68k_set_instr_hook_callback(NULL);
}