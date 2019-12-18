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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cpu_boot_arg ;
typedef  int /*<<< orphan*/  OpaqueDTEntryIterator ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 int DTInitEntryIterator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DTIterateEntries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ PE_parse_boot_argn (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ avail_cpus ; 
 int kSuccess ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ strncmp (char*,char*,unsigned int) ; 

void
ml_parse_cpu_topology(void)
{
	DTEntry entry, child;
	OpaqueDTEntryIterator iter;
	uint32_t cpu_boot_arg;
	int err;

	err = DTLookupEntry(NULL, "/cpus", &entry);
	assert(err == kSuccess);

	err = DTInitEntryIterator(entry, &iter);
	assert(err == kSuccess);

	while (kSuccess == DTIterateEntries(&iter, &child)) {

#if MACH_ASSERT
		unsigned int propSize;
		void *prop = NULL;
		if (avail_cpus == 0) {
			if (kSuccess != DTGetProperty(child, "state", &prop, &propSize))
				panic("unable to retrieve state for cpu %u", avail_cpus);

			if (strncmp((char*)prop, "running", propSize) != 0)
				panic("cpu 0 has not been marked as running!");
		}
		assert(kSuccess == DTGetProperty(child, "reg", &prop, &propSize));
		assert(avail_cpus == *((uint32_t*)prop));
#endif
		++avail_cpus;
	}

	cpu_boot_arg = avail_cpus;
	if (PE_parse_boot_argn("cpus", &cpu_boot_arg, sizeof(cpu_boot_arg)) &&
	    (avail_cpus > cpu_boot_arg))
		avail_cpus = cpu_boot_arg;

	if (avail_cpus == 0)
		panic("No cpus found!");
}