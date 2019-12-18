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
typedef  int /*<<< orphan*/  u32 ;
struct orc_scb {int scbidx; struct orc_extended_scb* escb; void* sense_addr; void* sg_addr; } ;
struct orc_host {scalar_t__ escb_phys; struct orc_extended_scb* escb_virt; struct orc_scb* scb_virt; scalar_t__ base; int /*<<< orphan*/  scb_phys; } ;
struct orc_extended_scb {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ORC_MAXQUEUE ; 
 scalar_t__ ORC_SCBBASE0 ; 
 scalar_t__ ORC_SCBBASE1 ; 
 scalar_t__ ORC_SCBSIZE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void setup_SCBs(struct orc_host * host)
{
	struct orc_scb *scb;
	int i;
	struct orc_extended_scb *escb;
	dma_addr_t escb_phys;

	/* Setup SCB base and SCB Size registers */
	outb(ORC_MAXQUEUE, host->base + ORC_SCBSIZE);	/* Total number of SCBs */
	/* SCB base address 0      */
	outl(host->scb_phys, host->base + ORC_SCBBASE0);
	/* SCB base address 1      */
	outl(host->scb_phys, host->base + ORC_SCBBASE1);

	/* setup scatter list address with one buffer */
	scb = host->scb_virt;
	escb = host->escb_virt;

	for (i = 0; i < ORC_MAXQUEUE; i++) {
		escb_phys = (host->escb_phys + (sizeof(struct orc_extended_scb) * i));
		scb->sg_addr = cpu_to_le32((u32) escb_phys);
		scb->sense_addr = cpu_to_le32((u32) escb_phys);
		scb->escb = escb;
		scb->scbidx = i;
		scb++;
		escb++;
	}
}