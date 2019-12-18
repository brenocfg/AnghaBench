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
typedef  int /*<<< orphan*/  temp_buf ;
typedef  int /*<<< orphan*/  fatal_memkill ;
typedef  int /*<<< orphan*/  exc_corpse_forking ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PE_parse_boot_argn (char*,...) ; 
 int /*<<< orphan*/  corpse_enabled_config ; 
 int corpse_for_fatal_memkill ; 
 int exc_via_corpse_forking ; 

void corpses_init(){
	char temp_buf[20];
	int exc_corpse_forking;
	int fatal_memkill;
	if (PE_parse_boot_argn("-no_corpses", temp_buf, sizeof(temp_buf))) {
		corpse_enabled_config = FALSE;
	}
	if (PE_parse_boot_argn("exc_via_corpse_forking", &exc_corpse_forking, sizeof(exc_corpse_forking))) {
		exc_via_corpse_forking = exc_corpse_forking;
	}
	if (PE_parse_boot_argn("corpse_for_fatal_memkill", &fatal_memkill, sizeof(fatal_memkill))) {
		corpse_for_fatal_memkill = fatal_memkill;
	}
}