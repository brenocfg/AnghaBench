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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  temp_bootarg_panic_trace ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTFindEntry (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ DTGetProperty (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PE_arm_debug_enable_trace () ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 unsigned int bootarg_panic_trace ; 
 int /*<<< orphan*/  cpu_halt ; 
 int /*<<< orphan*/  enable_alt_trace ; 
 int /*<<< orphan*/  enable_trace ; 
 scalar_t__ gSocPhys ; 
 scalar_t__ kSuccess ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  ml_init_arm_debug_interface (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_io_map (scalar_t__,uintptr_t) ; 
 int /*<<< orphan*/  panic_trace_lock ; 
 int /*<<< orphan*/  pe_init_debug_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_halt ; 

void
pe_arm_init_debug(void *args)
{
	DTEntry 	entryP;
	uintptr_t	*reg_prop;
	uint32_t	prop_size;

	if (gSocPhys == 0 ) {
		kprintf("pe_arm_init_debug: failed to initialize gSocPhys == 0\n");
	    return;
	}
	
	if ( DTFindEntry("device_type", "cpu-debug-interface", &entryP) == kSuccess ) {
		if (args != NULL) {
			if (DTGetProperty(entryP, "reg", (void **)&reg_prop, &prop_size) == kSuccess) {
				ml_init_arm_debug_interface(args, ml_io_map(gSocPhys + *reg_prop, *(reg_prop + 1)));
			}
#if DEVELOPMENT || DEBUG
			// When args != NULL, this means we're being called from arm_init on the boot CPU.
			// This controls one-time initialization of the Panic Trace infrastructure

			simple_lock_init(&panic_trace_lock, 0); //assuming single threaded mode
		
			// Panic_halt is deprecated. Please use panic_trace istead.
			unsigned int temp_bootarg_panic_trace;
			if (PE_parse_boot_argn("panic_trace", &temp_bootarg_panic_trace, sizeof(temp_bootarg_panic_trace)) ||
			    PE_parse_boot_argn("panic_halt", &temp_bootarg_panic_trace, sizeof(temp_bootarg_panic_trace))) {
		
				kprintf("pe_arm_init_debug: panic_trace=%d\n", temp_bootarg_panic_trace);

                // Prepare debug command buffers.
				pe_init_debug_command(entryP, &cpu_halt, "cpu_halt");
				pe_init_debug_command(entryP, &enable_trace, "enable_trace");
				pe_init_debug_command(entryP, &enable_alt_trace, "enable_alt_trace");
				pe_init_debug_command(entryP, &trace_halt, "trace_halt");
				
				// now that init's are done, enable the panic halt capture (allows pe_init_debug_command to panic normally if necessary)
				bootarg_panic_trace = temp_bootarg_panic_trace;

				// start tracing now if enabled
				PE_arm_debug_enable_trace();
			}
#endif
		}
	} else {
		kprintf("pe_arm_init_debug: failed to find cpu-debug-interface\n");
	}
}