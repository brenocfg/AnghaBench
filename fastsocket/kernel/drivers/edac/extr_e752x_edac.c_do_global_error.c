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
typedef  int u32 ;

/* Variables and functions */
 int DRAM_ENTRY ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fatal_message ; 
 int /*<<< orphan*/ * global_message ; 
 scalar_t__ report_non_memory_errors ; 

__attribute__((used)) static void do_global_error(int fatal, u32 errors)
{
	int i;

	for (i = 0; i < 11; i++) {
		if (errors & (1 << i)) {
			/* If the error is from DRAM Controller OR
			 * we are to report ALL errors, then
			 * report the error
			 */
			if ((i == DRAM_ENTRY) || report_non_memory_errors)
				e752x_printk(KERN_WARNING, "%sError %s\n",
					fatal_message[fatal],
					global_message[i]);
		}
	}
}