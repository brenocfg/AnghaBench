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
typedef  size_t u32 ;
struct sas_re_initialization_req {void* open_reject_cmdretries_data_retries; void* sata_hol_tmo; void* SSAHOLT; void* tag; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_ccb_info {size_t ccb_tag; } ;
struct inbound_queue_table {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 size_t OPC_INB_SAS_RE_INITIALIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct sas_re_initialization_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,size_t,struct sas_re_initialization_req*,int /*<<< orphan*/ ) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,size_t*) ; 

__attribute__((used)) static int
pm8001_chip_sas_re_initialization(struct pm8001_hba_info *pm8001_ha)
{
	struct sas_re_initialization_req payload;
	struct inbound_queue_table *circularQ;
	struct pm8001_ccb_info *ccb;
	int rc;
	u32 tag;
	u32 opc = OPC_INB_SAS_RE_INITIALIZE;
	memset(&payload, 0, sizeof(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		return -1;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->ccb_tag = tag;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.SSAHOLT = cpu_to_le32(0xd << 25);
	payload.sata_hol_tmo = cpu_to_le32(80);
	payload.open_reject_cmdretries_data_retries = cpu_to_le32(0xff00ff);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);
	return rc;

}