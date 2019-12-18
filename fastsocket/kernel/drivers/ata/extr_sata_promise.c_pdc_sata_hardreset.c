#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ata_link {TYPE_1__* ap; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int PDC_FLAG_GEN_II ; 
 int /*<<< orphan*/  pdc_hard_reset_port (TYPE_1__*) ; 
 int /*<<< orphan*/  pdc_not_at_command_packet_phase (TYPE_1__*) ; 
 int /*<<< orphan*/  pdc_reset_port (TYPE_1__*) ; 
 int sata_std_hardreset (struct ata_link*,unsigned int*,unsigned long) ; 

__attribute__((used)) static int pdc_sata_hardreset(struct ata_link *link, unsigned int *class,
			      unsigned long deadline)
{
	if (link->ap->flags & PDC_FLAG_GEN_II)
		pdc_not_at_command_packet_phase(link->ap);
	/* hotplug IRQs should have been masked by pdc_sata_freeze() */
	pdc_hard_reset_port(link->ap);
	pdc_reset_port(link->ap);

	/* sata_promise can't reliably acquire the first D2H Reg FIS
	 * after hardreset.  Do non-waiting hardreset and request
	 * follow-up SRST.
	 */
	return sata_std_hardreset(link, class, deadline);
}