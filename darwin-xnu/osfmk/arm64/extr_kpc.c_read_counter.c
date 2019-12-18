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
 int /*<<< orphan*/  SREG_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
read_counter(uint32_t counter)
{
	switch (counter) {
		// case 0: return SREG_READ(SREG_PMC0);
		// case 1: return SREG_READ(SREG_PMC1);
		case 2: return SREG_READ(SREG_PMC2);
		case 3: return SREG_READ(SREG_PMC3);
		case 4: return SREG_READ(SREG_PMC4);
		case 5: return SREG_READ(SREG_PMC5);
		case 6: return SREG_READ(SREG_PMC6);
		case 7: return SREG_READ(SREG_PMC7);
#if (KPC_ARM64_CONFIGURABLE_COUNT > 6)
		case 8: return SREG_READ(SREG_PMC8);
		case 9: return SREG_READ(SREG_PMC9);
#endif
		default: return 0;
	}
}