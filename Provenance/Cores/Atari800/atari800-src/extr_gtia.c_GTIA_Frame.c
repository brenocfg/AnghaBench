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
 int GTIA_GRACTL ; 
 int /*<<< orphan*/ * GTIA_TRIG ; 
 int /*<<< orphan*/ * GTIA_TRIG_latch ; 
 int INPUT_key_consol ; 
 int consol ; 

void GTIA_Frame(void)
{
#ifdef BASIC
	consol = 0xf;
#else
	consol = INPUT_key_consol | 0x08;
#endif

	if (GTIA_GRACTL & 4) {
		GTIA_TRIG_latch[0] &= GTIA_TRIG[0];
		GTIA_TRIG_latch[1] &= GTIA_TRIG[1];
		GTIA_TRIG_latch[2] &= GTIA_TRIG[2];
		GTIA_TRIG_latch[3] &= GTIA_TRIG[3];
	}
}