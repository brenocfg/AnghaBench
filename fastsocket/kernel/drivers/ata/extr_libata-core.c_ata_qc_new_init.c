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
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; int /*<<< orphan*/ * scsicmd; } ;
struct ata_port {int dummy; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_port* ap; } ;

/* Variables and functions */
 struct ata_queued_cmd* ata_qc_new (struct ata_port*) ; 
 int /*<<< orphan*/  ata_qc_reinit (struct ata_queued_cmd*) ; 

struct ata_queued_cmd *ata_qc_new_init(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_queued_cmd *qc;

	qc = ata_qc_new(ap);
	if (qc) {
		qc->scsicmd = NULL;
		qc->ap = ap;
		qc->dev = dev;

		ata_qc_reinit(qc);
	}

	return qc;
}