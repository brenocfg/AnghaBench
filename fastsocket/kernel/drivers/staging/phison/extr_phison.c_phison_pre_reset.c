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
struct ata_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  cbl; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_NONE ; 
 int ata_std_prereset (struct ata_link*,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int phison_pre_reset(struct ata_link *link, unsigned long deadline)
{
	int ret;
	struct ata_port *ap = link->ap;

	ap->cbl = ATA_CBL_NONE;
	ret = ata_std_prereset(link, deadline);
	dev_dbg(ap->dev, "phison_pre_reset(), ret = %x\n", ret);
	return ret;
}