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
 int /*<<< orphan*/  CPU_GenerateIRQ () ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int PBI_IRQ ; 
 int /*<<< orphan*/  POKEY_IRQEN ; 
 int /*<<< orphan*/  POKEY_OFFSET_IRQEN ; 
 int /*<<< orphan*/  POKEY_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VOICE_MASK ; 
 int /*<<< orphan*/  printf (char*) ; 
 int votrax_latch ; 

void PBI_XLD_votrax_busy_callback(int busy_status)
{
	if (!busy_status && (votrax_latch & 0x80)){
		/* busy->idle and IRQ enabled */
		D(printf("votrax IRQ generated\n"));
		CPU_GenerateIRQ();		
		PBI_IRQ |= VOICE_MASK;
	}
	else if (busy_status && (PBI_IRQ & VOICE_MASK)) {
		/* idle->busy and PBI_IRQ set */
		PBI_IRQ &= ~VOICE_MASK;
		/* update pokey IRQ status */
		POKEY_PutByte(POKEY_OFFSET_IRQEN, POKEY_IRQEN);
	}
}