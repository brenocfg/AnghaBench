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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_GetStatus () ; 
 int /*<<< orphan*/  CPU_IRQ ; 
 int /*<<< orphan*/  CPU_regA ; 
 int /*<<< orphan*/  CPU_regP ; 
 int /*<<< orphan*/  CPU_regPC ; 
 int /*<<< orphan*/  CPU_regS ; 
 int /*<<< orphan*/  CPU_regX ; 
 int /*<<< orphan*/  CPU_regY ; 
 int /*<<< orphan*/  MEMORY_StateSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_SaveUWORD (int /*<<< orphan*/ *,int) ; 

void CPU_StateSave(UBYTE SaveVerbose)
{
	StateSav_SaveUBYTE(&CPU_regA, 1);

	CPU_GetStatus();	/* Make sure flags are all updated */
	StateSav_SaveUBYTE(&CPU_regP, 1);

	StateSav_SaveUBYTE(&CPU_regS, 1);
	StateSav_SaveUBYTE(&CPU_regX, 1);
	StateSav_SaveUBYTE(&CPU_regY, 1);
	StateSav_SaveUBYTE(&CPU_IRQ, 1);

	MEMORY_StateSave(SaveVerbose);

	StateSav_SaveUWORD(&CPU_regPC, 1);
}