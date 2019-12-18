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
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 int /*<<< orphan*/  setup_summit () ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int use_cyclone ; 

__attribute__((used)) static int summit_acpi_madt_oem_check(char *oem_id, char *oem_table_id)
{
	if (!strncmp(oem_id, "IBM", 3) &&
	    (!strncmp(oem_table_id, "SERVIGIL", 8)
	     || !strncmp(oem_table_id, "EXA", 3))){
		mark_tsc_unstable("Summit based system");
		use_cyclone = 1; /*enable cyclone-timer*/
		setup_summit();
		return 1;
	}
	return 0;
}