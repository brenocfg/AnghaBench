#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct domain_device {scalar_t__ dev_type; scalar_t__ frame_rcvd; scalar_t__ lldd_dev; TYPE_2__* port; } ;
struct dev_to_host_fis {int /*<<< orphan*/  status; } ;
struct asd_ha_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ha; } ;
struct TYPE_3__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_SCBPTR ; 
 int /*<<< orphan*/  NCQ_DATA_SCB_PTR ; 
 scalar_t__ SATA_DEV ; 
 scalar_t__ SATA_PM ; 
 scalar_t__ SATA_PM_PORT ; 
 int /*<<< orphan*/  SATA_STATUS ; 
 int /*<<< orphan*/  asd_ddbsite_write_byte (struct asd_ha_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_ddbsite_write_word (struct asd_ha_struct*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asd_init_sata(struct domain_device *dev)
{
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;
	int ddb = (int) (unsigned long) dev->lldd_dev;

	asd_ddbsite_write_word(asd_ha, ddb, ATA_CMD_SCBPTR, 0xFFFF);
	if (dev->dev_type == SATA_DEV || dev->dev_type == SATA_PM ||
	    dev->dev_type == SATA_PM_PORT) {
		struct dev_to_host_fis *fis = (struct dev_to_host_fis *)
			dev->frame_rcvd;
		asd_ddbsite_write_byte(asd_ha, ddb, SATA_STATUS, fis->status);
	}
	asd_ddbsite_write_word(asd_ha, ddb, NCQ_DATA_SCB_PTR, 0xFFFF);

	return 0;
}