#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sccbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_SCCA ; 
 int /*<<< orphan*/  IRQ_SCCB ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  m68k_handle_int (int /*<<< orphan*/ ) ; 
 TYPE_1__ mac_bi_data ; 

void mac_scc_dispatch(int irq, void *dev_id)
{
	volatile unsigned char *scc = (unsigned char *) mac_bi_data.sccbase + 2;
	unsigned char reg;
	unsigned long flags;

	/* Read RR3 from the chip. Always do this on channel A */
	/* This must be an atomic operation so disable irqs.   */

	local_irq_save(flags);
	*scc = 3;
	reg = *scc;
	local_irq_restore(flags);

	/* Now dispatch. Bits 0-2 are for channel B and */
	/* bits 3-5 are for channel A. We can safely    */
	/* ignore the remaining bits here.              */
	/*                                              */
	/* Note that we're ignoring scc_mask for now.   */
	/* If we actually mask the ints then we tend to */
	/* get hammered by very persistent SCC irqs,    */
	/* and since they're autovector interrupts they */
	/* pretty much kill the system.                 */

	if (reg & 0x38)
		m68k_handle_int(IRQ_SCCA);
	if (reg & 0x07)
		m68k_handle_int(IRQ_SCCB);
}