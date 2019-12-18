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
 int /*<<< orphan*/  PBI_D1PutByte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ PBI_IRQ ; 
 int /*<<< orphan*/  PBI_XLD_Reset () ; 
 scalar_t__ PBI_XLD_enabled ; 

void PBI_Reset(void)
{
	/* Reset all PBI ROMs */
	PBI_D1PutByte(0xd1ff, 0);
#ifdef PBI_XLD
	if (PBI_XLD_enabled) PBI_XLD_Reset();
#endif
	PBI_IRQ = 0;
}