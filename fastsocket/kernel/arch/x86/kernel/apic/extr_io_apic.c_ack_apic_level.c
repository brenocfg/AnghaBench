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
struct irq_desc {int status; struct irq_cfg* chip_data; } ;
struct irq_cfg {int vector; } ;

/* Variables and functions */
 scalar_t__ APIC_TMR ; 
 int IRQ_MOVE_PENDING ; 
 int /*<<< orphan*/  ack_APIC_irq () ; 
 unsigned long apic_read (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eoi_ioapic_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  io_apic_level_ack_pending (struct irq_cfg*) ; 
 int /*<<< orphan*/  irq_complete_move (struct irq_desc**) ; 
 int /*<<< orphan*/  irq_mis_count ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  mask_IO_APIC_irq_desc (struct irq_desc*) ; 
 int /*<<< orphan*/  move_masked_irq (unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmask_IO_APIC_irq_desc (struct irq_desc*) ; 

__attribute__((used)) static void ack_apic_level(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long v;
	int i;
	struct irq_cfg *cfg;
	int do_unmask_irq = 0;

	irq_complete_move(&desc);
#ifdef CONFIG_GENERIC_PENDING_IRQ
	/* If we are moving the irq we need to mask it */
	if (unlikely(desc->status & IRQ_MOVE_PENDING)) {
		do_unmask_irq = 1;
		mask_IO_APIC_irq_desc(desc);
	}
#endif

	/*
	 * It appears there is an erratum which affects at least version 0x11
	 * of I/O APIC (that's the 82093AA and cores integrated into various
	 * chipsets).  Under certain conditions a level-triggered interrupt is
	 * erroneously delivered as edge-triggered one but the respective IRR
	 * bit gets set nevertheless.  As a result the I/O unit expects an EOI
	 * message but it will never arrive and further interrupts are blocked
	 * from the source.  The exact reason is so far unknown, but the
	 * phenomenon was observed when two consecutive interrupt requests
	 * from a given source get delivered to the same CPU and the source is
	 * temporarily disabled in between.
	 *
	 * A workaround is to simulate an EOI message manually.  We achieve it
	 * by setting the trigger mode to edge and then to level when the edge
	 * trigger mode gets detected in the TMR of a local APIC for a
	 * level-triggered interrupt.  We mask the source for the time of the
	 * operation to prevent an edge-triggered interrupt escaping meanwhile.
	 * The idea is from Manfred Spraul.  --macro
	 *
	 * Also in the case when cpu goes offline, fixup_irqs() will forward
	 * any unhandled interrupt on the offlined cpu to the new cpu
	 * destination that is handling the corresponding interrupt. This
	 * interrupt forwarding is done via IPI's. Hence, in this case also
	 * level-triggered io-apic interrupt will be seen as an edge
	 * interrupt in the IRR. And we can't rely on the cpu's EOI
	 * to be broadcasted to the IO-APIC's which will clear the remoteIRR
	 * corresponding to the level-triggered interrupt. Hence on IO-APIC's
	 * supporting EOI register, we do an explicit EOI to clear the
	 * remote IRR and on IO-APIC's which don't have an EOI register,
	 * we use the above logic (mask+edge followed by unmask+level) from
	 * Manfred Spraul to clear the remote IRR.
	 */
	cfg = desc->chip_data;
	i = cfg->vector;
	v = apic_read(APIC_TMR + ((i & ~0x1f) >> 1));

	/*
	 * We must acknowledge the irq before we move it or the acknowledge will
	 * not propagate properly.
	 */
	ack_APIC_irq();

	/*
	 * Tail end of clearing remote IRR bit (either by delivering the EOI
	 * message via io-apic EOI register write or simulating it using
	 * mask+edge followed by unnask+level logic) manually when the
	 * level triggered interrupt is seen as the edge triggered interrupt
	 * at the cpu.
	 */
	if (!(v & (1 << (i & 0x1f)))) {
		atomic_inc(&irq_mis_count);

		eoi_ioapic_irq(desc);
	}

	/* Now we can move and renable the irq */
	if (unlikely(do_unmask_irq)) {
		/* Only migrate the irq if the ack has been received.
		 *
		 * On rare occasions the broadcast level triggered ack gets
		 * delayed going to ioapics, and if we reprogram the
		 * vector while Remote IRR is still set the irq will never
		 * fire again.
		 *
		 * To prevent this scenario we read the Remote IRR bit
		 * of the ioapic.  This has two effects.
		 * - On any sane system the read of the ioapic will
		 *   flush writes (and acks) going to the ioapic from
		 *   this cpu.
		 * - We get to see if the ACK has actually been delivered.
		 *
		 * Based on failed experiments of reprogramming the
		 * ioapic entry from outside of irq context starting
		 * with masking the ioapic entry and then polling until
		 * Remote IRR was clear before reprogramming the
		 * ioapic I don't trust the Remote IRR bit to be
		 * completey accurate.
		 *
		 * However there appears to be no other way to plug
		 * this race, so if the Remote IRR bit is not
		 * accurate and is causing problems then it is a hardware bug
		 * and you can go talk to the chipset vendor about it.
		 */
		cfg = desc->chip_data;
		if (!io_apic_level_ack_pending(cfg))
			move_masked_irq(irq);
		unmask_IO_APIC_irq_desc(desc);
	}
}