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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_800 ; 
 scalar_t__ Atari800_machine_type ; 
 int MEMORY_axlon_num_banks ; 
 scalar_t__ Util_realloc (int /*<<< orphan*/ *,int) ; 
 int axlon_current_bankmask ; 
 int /*<<< orphan*/ * axlon_ram ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alloc_axlon_memory(void){
	if (MEMORY_axlon_num_banks > 0 && Atari800_machine_type == Atari800_MACHINE_800) {
		int size = MEMORY_axlon_num_banks * 0x4000;
		if (axlon_ram == NULL || axlon_current_bankmask != MEMORY_axlon_num_banks - 1) {
			axlon_current_bankmask = MEMORY_axlon_num_banks - 1;
			axlon_ram = (UBYTE *)Util_realloc(axlon_ram, size);
		}
		memset(axlon_ram, 0, size);
	} else {
		if (axlon_ram != NULL) {
			free(axlon_ram);
			axlon_ram = NULL;
			axlon_current_bankmask = 0;
		}
	}
}