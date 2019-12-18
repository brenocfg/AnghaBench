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
typedef  void* uint32_t ;
struct embedded_panic_header {char eph_magic; } ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 scalar_t__ DTLookupEntry (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char EMBEDDED_PANIC_MAGIC ; 
 uintptr_t PLATFORM_PANIC_LOG_PADDR ; 
 void* PLATFORM_PANIC_LOG_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (void*,void*) ; 
 scalar_t__ gPanicBase ; 
 void* gPanicSize ; 
 scalar_t__ kSuccess ; 
 scalar_t__ ml_io_map_wcomb (uintptr_t,void*) ; 
 int /*<<< orphan*/  panic_console_available ; 
 struct embedded_panic_header* panic_info ; 
 void* panic_text_len ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
check_for_panic_log(void)
{
#ifdef PLATFORM_PANIC_LOG_PADDR
	gPanicBase = ml_io_map_wcomb(PLATFORM_PANIC_LOG_PADDR, PLATFORM_PANIC_LOG_SIZE);
	panic_text_len = PLATFORM_PANIC_LOG_SIZE - sizeof(struct embedded_panic_header);
	gPanicSize = PLATFORM_PANIC_LOG_SIZE;
#else
	DTEntry entry, chosen;
	unsigned int size;
	uintptr_t *reg_prop;
	uint32_t *panic_region_length;

	/*
	 * Find the vram node in the device tree
	 */
	if (kSuccess != DTLookupEntry(0, "pram", &entry))
		return;

	if (kSuccess != DTGetProperty(entry, "reg", (void **)&reg_prop, &size))
		return;

	if (kSuccess != DTLookupEntry(0, "/chosen", &chosen))
		return;

	if (kSuccess != DTGetProperty(chosen, "embedded-panic-log-size", (void **) &panic_region_length, &size))
		return;

	/*
	 * Map the first page of VRAM into the kernel for use in case of
	 * panic
	 */
	/* Note: map as normal memory. */
	gPanicBase = ml_io_map_wcomb(reg_prop[0], panic_region_length[0]);

	/* Deduct the size of the panic header from the panic region size */
	panic_text_len = panic_region_length[0] - sizeof(struct embedded_panic_header);
	gPanicSize = panic_region_length[0];
#endif
	panic_info = (struct embedded_panic_header *)gPanicBase;

	/* Check if a shared memory console is running in the panic buffer */
	if (panic_info->eph_magic == 'SHMC') {
		panic_console_available = TRUE;
		return;
	}

	/* Check if there's a boot profile in the panic buffer */
	if (panic_info->eph_magic == 'BTRC') {
		return;
	}

	/*
	 * Check to see if a panic (FUNK) is in VRAM from the last time
	 */
	if (panic_info->eph_magic == EMBEDDED_PANIC_MAGIC) {
		printf("iBoot didn't extract panic log from previous session crash, this is bad\n");
	}

	/* Clear panic region */
	bzero((void *)gPanicBase, gPanicSize);
}