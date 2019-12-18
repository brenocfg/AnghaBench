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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sas_identify_frame {int /*<<< orphan*/  sas_addr; } ;
struct TYPE_4__ {int* frame_rcvd; scalar_t__ oob_mode; scalar_t__ id; TYPE_1__* ha; } ;
struct pm8001_phy {TYPE_2__ sas_phy; } ;
struct pm8001_hba_info {scalar_t__ sas_addr; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_3__ {struct pm8001_hba_info* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ SATA_OOB_MODE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pm8001_get_attached_sas_addr(struct pm8001_phy *phy,
	u8 *sas_addr)
{
	if (phy->sas_phy.frame_rcvd[0] == 0x34
		&& phy->sas_phy.oob_mode == SATA_OOB_MODE) {
		struct pm8001_hba_info *pm8001_ha = phy->sas_phy.ha->lldd_ha;
		/* FIS device-to-host */
		u64 addr = be64_to_cpu(*(__be64 *)pm8001_ha->sas_addr);
		addr += phy->sas_phy.id;
		*(__be64 *)sas_addr = cpu_to_be64(addr);
	} else {
		struct sas_identify_frame *idframe =
			(void *) phy->sas_phy.frame_rcvd;
		memcpy(sas_addr, idframe->sas_addr, SAS_ADDR_SIZE);
	}
}