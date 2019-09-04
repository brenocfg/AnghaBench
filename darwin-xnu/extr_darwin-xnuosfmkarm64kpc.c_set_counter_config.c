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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMESR_EVT_CLEAR (int,int) ; 
 int /*<<< orphan*/  PMESR_EVT_ENCODE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SREG_PMESR0 ; 
 int /*<<< orphan*/  SREG_PMESR1 ; 
 int /*<<< orphan*/  SREG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpu_number () ; 
 int /*<<< orphan*/ ** saved_PMESR ; 
 int /*<<< orphan*/  set_modes (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_counter_config(uint32_t counter, uint64_t config)
{
	int cpuid = cpu_number();
	uint64_t pmesr = 0;

	switch (counter) {
		case 2: /* FALLTHROUGH */
		case 3: /* FALLTHROUGH */
		case 4: /* FALLTHROUGH */
		case 5:
			pmesr = SREG_READ(SREG_PMESR0);
			pmesr &= PMESR_EVT_CLEAR(counter, 2);
			pmesr |= PMESR_EVT_ENCODE(config, counter, 2);
			SREG_WRITE(SREG_PMESR0, pmesr);
			saved_PMESR[cpuid][0] = pmesr;
			break;

		case 6: /* FALLTHROUGH */
		case 7:
#if KPC_ARM64_CONFIGURABLE_COUNT > 6
			/* FALLTHROUGH */
		case 8: /* FALLTHROUGH */
		case 9:
#endif
			pmesr = SREG_READ(SREG_PMESR1);
			pmesr &= PMESR_EVT_CLEAR(counter, 6);
			pmesr |= PMESR_EVT_ENCODE(config, counter, 6);
			SREG_WRITE(SREG_PMESR1, pmesr);
			saved_PMESR[cpuid][1] = pmesr;
			break;
		default:
			break;
	}

	set_modes(counter, config);
}