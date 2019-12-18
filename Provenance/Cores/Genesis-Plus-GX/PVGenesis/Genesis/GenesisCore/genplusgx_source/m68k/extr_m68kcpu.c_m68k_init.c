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
 int /*<<< orphan*/  m68k_set_fc_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_int_ack_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_reset_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_tas_instr_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68ki_build_opcode_table () ; 

void m68k_init(void)
{
#ifdef BUILD_TABLES
  static uint emulation_initialized = 0;

  /* The first call to this function initializes the opcode handler jump table */
  if(!emulation_initialized)
  {
    m68ki_build_opcode_table();
    emulation_initialized = 1;
  }
#endif

#if M68K_EMULATE_INT_ACK == OPT_ON
  m68k_set_int_ack_callback(NULL);
#endif
#if M68K_EMULATE_RESET == OPT_ON
  m68k_set_reset_instr_callback(NULL);
#endif
#if M68K_TAS_HAS_CALLBACK == OPT_ON
  m68k_set_tas_instr_callback(NULL);
#endif
#if M68K_EMULATE_FC == OPT_ON
  m68k_set_fc_callback(NULL);
#endif
}