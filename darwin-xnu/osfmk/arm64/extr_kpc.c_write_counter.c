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
 int /*<<< orphan*/  SREG_PMC2 ; 
 int /*<<< orphan*/  SREG_PMC3 ; 
 int /*<<< orphan*/  SREG_PMC4 ; 
 int /*<<< orphan*/  SREG_PMC5 ; 
 int /*<<< orphan*/  SREG_PMC6 ; 
 int /*<<< orphan*/  SREG_PMC7 ; 
 int /*<<< orphan*/  SREG_PMC8 ; 
 int /*<<< orphan*/  SREG_PMC9 ; 
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_counter(uint32_t counter, uint64_t value)
{
	switch (counter) {
		// case 0: SREG_WRITE(SREG_PMC0, value); break;
		// case 1: SREG_WRITE(SREG_PMC1, value); break;
		case 2: SREG_WRITE(SREG_PMC2, value); break;
		case 3: SREG_WRITE(SREG_PMC3, value); break;
		case 4: SREG_WRITE(SREG_PMC4, value); break;
		case 5: SREG_WRITE(SREG_PMC5, value); break;
		case 6: SREG_WRITE(SREG_PMC6, value); break;
		case 7: SREG_WRITE(SREG_PMC7, value); break;
#if (KPC_ARM64_CONFIGURABLE_COUNT > 6)
		case 8: SREG_WRITE(SREG_PMC8, value); break;
		case 9: SREG_WRITE(SREG_PMC9, value); break;
#endif
		default: break;
	}
}