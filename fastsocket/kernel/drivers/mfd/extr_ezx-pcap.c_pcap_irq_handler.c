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
struct pcap_chip {int /*<<< orphan*/  isr_work; int /*<<< orphan*/  workqueue; } ;
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (unsigned int) ;} ;

/* Variables and functions */
 struct pcap_chip* get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void pcap_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	struct pcap_chip *pcap = get_irq_data(irq);

	desc->chip->ack(irq);
	queue_work(pcap->workqueue, &pcap->isr_work);
	return;
}