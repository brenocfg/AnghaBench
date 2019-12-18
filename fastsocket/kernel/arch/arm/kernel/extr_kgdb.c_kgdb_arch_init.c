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
 int /*<<< orphan*/  kgdb_brkpt_hook ; 
 int /*<<< orphan*/  kgdb_compiled_brkpt_hook ; 
 int /*<<< orphan*/  register_undef_hook (int /*<<< orphan*/ *) ; 

int kgdb_arch_init(void)
{
	register_undef_hook(&kgdb_brkpt_hook);
	register_undef_hook(&kgdb_compiled_brkpt_hook);

	return 0;
}