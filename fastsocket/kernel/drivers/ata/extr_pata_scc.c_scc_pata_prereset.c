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
struct ata_link {TYPE_1__* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  cbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 int ata_sff_prereset (struct ata_link*,unsigned long) ; 

__attribute__((used)) static int scc_pata_prereset(struct ata_link *link, unsigned long deadline)
{
	link->ap->cbl = ATA_CBL_PATA80;
	return ata_sff_prereset(link, deadline);
}