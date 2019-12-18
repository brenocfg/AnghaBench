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
 int /*<<< orphan*/  kgdb_arch_exit () ; 
 scalar_t__ kgdb_con_registered ; 
 scalar_t__ kgdb_io_module_registered ; 
 int /*<<< orphan*/  kgdbcons ; 
 int /*<<< orphan*/  sysrq_gdb_op ; 
 int /*<<< orphan*/  unregister_console (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sysrq_key (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kgdb_unregister_callbacks(void)
{
	/*
	 * When this routine is called KGDB should unregister from the
	 * panic handler and clean up, making sure it is not handling any
	 * break exceptions at the time.
	 */
	if (kgdb_io_module_registered) {
		kgdb_io_module_registered = 0;
		kgdb_arch_exit();
#ifdef CONFIG_MAGIC_SYSRQ
		unregister_sysrq_key('g', &sysrq_gdb_op);
#endif
		if (kgdb_con_registered) {
			unregister_console(&kgdbcons);
			kgdb_con_registered = 0;
		}
	}
}