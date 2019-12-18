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
 int /*<<< orphan*/  BOOT_MEM_RAM ; 
 int CHUNK_SIZE ; 
 scalar_t__ CKSEG0 ; 
 unsigned long CKSEG1 ; 
 int /*<<< orphan*/  add_memory_region (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_err ; 
 int /*<<< orphan*/  memcpy (void*,...) ; 

__attribute__((used)) static inline void pmax_setup_memory_region(void)
{
	volatile unsigned char *memory_page, dummy;
	char old_handler[0x80];
	extern char genexcept_early;

	/* Install exception handler */
	memcpy(&old_handler, (void *)(CKSEG0 + 0x80), 0x80);
	memcpy((void *)(CKSEG0 + 0x80), &genexcept_early, 0x80);

	/* read unmapped and uncached (KSEG1)
	 * DECstations have at least 4MB RAM
	 * Assume less than 480MB of RAM, as this is max for 5000/2xx
	 * FIXME this should be replaced by the first free page!
	 */
	for (memory_page = (unsigned char *)CKSEG1 + CHUNK_SIZE;
	     mem_err == 0 && memory_page < (unsigned char *)CKSEG1 + 0x1e00000;
	     memory_page += CHUNK_SIZE) {
		dummy = *memory_page;
	}
	memcpy((void *)(CKSEG0 + 0x80), &old_handler, 0x80);

	add_memory_region(0, (unsigned long)memory_page - CKSEG1 - CHUNK_SIZE,
			  BOOT_MEM_RAM);
}