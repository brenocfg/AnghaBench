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
struct domain_device {scalar_t__ lldd_dev; TYPE_2__* port; } ;
struct asd_ha_struct {int dummy; } ;
struct asd_ddb_sata_tag {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ha; } ;
struct TYPE_3__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int SISTER_DDB ; 
 int /*<<< orphan*/  asd_ddbsite_write_word (struct asd_ha_struct*,int,int,int) ; 
 int asd_get_ddb (struct asd_ha_struct*) ; 

__attribute__((used)) static int asd_init_sata_tag_ddb(struct domain_device *dev)
{
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;
	int ddb, i;

	ddb = asd_get_ddb(asd_ha);
	if (ddb < 0)
		return ddb;

	for (i = 0; i < sizeof(struct asd_ddb_sata_tag); i += 2)
		asd_ddbsite_write_word(asd_ha, ddb, i, 0xFFFF);

	asd_ddbsite_write_word(asd_ha, (int) (unsigned long) dev->lldd_dev,
			       SISTER_DDB, ddb);
	return 0;
}