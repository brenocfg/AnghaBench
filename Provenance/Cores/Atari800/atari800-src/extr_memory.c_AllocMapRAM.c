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
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_machine_type ; 
 scalar_t__ MEMORY_enable_mapram ; 
 int MEMORY_ram_size ; 
 scalar_t__ Util_malloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mapram_memory ; 

__attribute__((used)) static void AllocMapRAM(void)
{
	if (MEMORY_enable_mapram && Atari800_machine_type == Atari800_MACHINE_XLXE
	    && MEMORY_ram_size > 20) {
		if (mapram_memory == NULL)
			mapram_memory = (UBYTE *)Util_malloc(0x800);
	}
	else if (mapram_memory != NULL) {
		free(mapram_memory);
		mapram_memory = NULL;
	}
}