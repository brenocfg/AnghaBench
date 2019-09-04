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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ __improbable (int) ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ machine_timeout_suspended () ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,uintptr_t,scalar_t__,...) ; 
 scalar_t__ phyreadpanic ; 
 scalar_t__ reportphyreaddelayabs ; 

unsigned long long ml_io_read(uintptr_t vaddr, int size) {
	unsigned long long result = 0;
	unsigned char s1;
	unsigned short s2;

#if defined(__x86_64__)
	uint64_t sabs, eabs;
	boolean_t istate, timeread = FALSE;
#if DEVELOPMENT || DEBUG
	pmap_verify_noncacheable(vaddr);
#endif /* x86_64 DEVELOPMENT || DEBUG */
	if (__improbable(reportphyreaddelayabs != 0)) {
		istate = ml_set_interrupts_enabled(FALSE);
		sabs = mach_absolute_time();
		timeread = TRUE;
	}
#endif /* x86_64 */

	switch (size) {
        case 1:
		s1 = *(volatile unsigned char *)vaddr;
		result = s1;
		break;
        case 2:
		s2 = *(volatile unsigned short *)vaddr;
		result = s2;
		break;
        case 4:
		result = *(volatile unsigned int *)vaddr;
		break;
	case 8:
		result = *(volatile unsigned long long *)vaddr;
		break;
	default:
		panic("Invalid size %d for ml_io_read(%p)\n", size, (void *)vaddr);
		break;
        }

#if defined(__x86_64__)
	if (__improbable(timeread == TRUE)) {
		eabs = mach_absolute_time();
		(void)ml_set_interrupts_enabled(istate);

		if (__improbable((eabs - sabs) > reportphyreaddelayabs)) {
			if (phyreadpanic && (machine_timeout_suspended() == FALSE)) {
				panic("Read from IO virtual addr 0x%lx took %llu ns, result: 0x%llx (start: %llu, end: %llu), ceiling: %llu", vaddr, (eabs - sabs), result, sabs, eabs, reportphyreaddelayabs);
			}
#if CONFIG_DTRACE
			DTRACE_PHYSLAT3(physread, uint64_t, (eabs - sabs),
			    uint64_t, vaddr, uint32_t, size);
#endif /* CONFIG_DTRACE */
		}
	}
#endif /* x86_64 */
	return result;
}