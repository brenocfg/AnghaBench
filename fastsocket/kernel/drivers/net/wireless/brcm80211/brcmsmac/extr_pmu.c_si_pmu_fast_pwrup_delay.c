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
typedef  int uint ;
typedef  int /*<<< orphan*/  u16 ;
struct si_pub {int dummy; } ;

/* Variables and functions */
#define  BCM4313_CHIP_ID 130 
#define  BCM43224_CHIP_ID 129 
#define  BCM43225_CHIP_ID 128 
 int PMU_MAX_TRANSITION_DLY ; 
 int ai_get_chip_id (struct si_pub*) ; 

u16 si_pmu_fast_pwrup_delay(struct si_pub *sih)
{
	uint delay = PMU_MAX_TRANSITION_DLY;

	switch (ai_get_chip_id(sih)) {
	case BCM43224_CHIP_ID:
	case BCM43225_CHIP_ID:
	case BCM4313_CHIP_ID:
		delay = 3700;
		break;
	default:
		break;
	}

	return (u16) delay;
}