#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {int port_no; } ;
struct domain_device {TYPE_4__ sata_dev; TYPE_3__* parent; TYPE_2__* port; } ;
struct asd_ha_struct {int dummy; } ;
struct TYPE_7__ {scalar_t__ lldd_dev; } ;
struct TYPE_6__ {TYPE_1__* ha; } ;
struct TYPE_5__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int ATA_CMD_SCBPTR ; 
 int /*<<< orphan*/  NUM_SATA_TAGS ; 
 int PARENT_DDB ; 
 int /*<<< orphan*/  PM_PORT_FLAGS ; 
 int PM_PORT_SET ; 
 int SISTER_DDB ; 
 scalar_t__ asd_ddbsite_read_byte (struct asd_ha_struct*,int,int /*<<< orphan*/ ) ; 
 int asd_ddbsite_read_word (struct asd_ha_struct*,int,int) ; 
 int /*<<< orphan*/  asd_ddbsite_write_byte (struct asd_ha_struct*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asd_ddbsite_write_word (struct asd_ha_struct*,int,int,int) ; 
 int /*<<< orphan*/  asd_free_ddb (struct asd_ha_struct*,int) ; 
 int asd_get_ddb (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_init_sata (struct domain_device*) ; 
 int asd_init_sata_tag_ddb (struct domain_device*) ; 
 int /*<<< orphan*/  asd_set_ddb_type (struct domain_device*) ; 

__attribute__((used)) static int asd_init_sata_pm_port_ddb(struct domain_device *dev)
{
	int ddb, i, parent_ddb, pmtable_ddb;
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;
	u8  flags;

	ddb = asd_get_ddb(asd_ha);
	if (ddb < 0)
		return ddb;

	asd_set_ddb_type(dev);
	flags = (dev->sata_dev.port_no << 4) | PM_PORT_SET;
	asd_ddbsite_write_byte(asd_ha, ddb, PM_PORT_FLAGS, flags);
	asd_ddbsite_write_word(asd_ha, ddb, SISTER_DDB, 0xFFFF);
	asd_ddbsite_write_word(asd_ha, ddb, ATA_CMD_SCBPTR, 0xFFFF);
	asd_init_sata(dev);

	parent_ddb = (int) (unsigned long) dev->parent->lldd_dev;
	asd_ddbsite_write_word(asd_ha, ddb, PARENT_DDB, parent_ddb);
	pmtable_ddb = asd_ddbsite_read_word(asd_ha, parent_ddb, SISTER_DDB);
	asd_ddbsite_write_word(asd_ha, pmtable_ddb, dev->sata_dev.port_no,ddb);

	if (asd_ddbsite_read_byte(asd_ha, ddb, NUM_SATA_TAGS) > 0) {
		i = asd_init_sata_tag_ddb(dev);
		if (i < 0) {
			asd_free_ddb(asd_ha, ddb);
			return i;
		}
	}
	return 0;
}