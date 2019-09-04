#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boot_arg ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {scalar_t__ initialized; } ;

/* Variables and functions */
 unsigned int DB_KPRT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PE_kputc ; 
 scalar_t__ PE_parse_boot_argn (char*,unsigned int*,int) ; 
 TYPE_1__ PE_state ; 
 int /*<<< orphan*/  cnputc ; 
 scalar_t__ disable_serial_output ; 
 int /*<<< orphan*/  kprintf_lock ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ serial_init () ; 
 int /*<<< orphan*/  serial_putc ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
PE_init_kprintf(boolean_t vm_initialized)
{
	unsigned int    boot_arg;

	if (PE_state.initialized == FALSE)
		panic("Platform Expert not initialized");

	if (!vm_initialized) {
		simple_lock_init(&kprintf_lock, 0);

		if (PE_parse_boot_argn("debug", &boot_arg, sizeof (boot_arg)))
			if (boot_arg & DB_KPRT)
				disable_serial_output = FALSE;

		if (serial_init())
			PE_kputc = serial_putc;
		else
			PE_kputc = cnputc;
	}
}