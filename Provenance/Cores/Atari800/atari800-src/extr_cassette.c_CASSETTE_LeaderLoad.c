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
 int /*<<< orphan*/  CASSETTE_TapeMotor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CASSETTE_ToggleRecord () ; 
 scalar_t__ CASSETTE_record ; 
 int CPU_regA ; 
 scalar_t__ CPU_regX ; 
 int CPU_regY ; 
 int /*<<< orphan*/  TRUE ; 
 int cassette_gapdelay ; 

void CASSETTE_LeaderLoad(void)
{
	if (CASSETTE_record)
		CASSETTE_ToggleRecord();
	CASSETTE_TapeMotor(TRUE);
	cassette_gapdelay = 9600;
	/* registers for SETVBV: third system timer, ~0.1 sec */
	CPU_regA = 3;
	CPU_regX = 0;
	CPU_regY = 5;
}