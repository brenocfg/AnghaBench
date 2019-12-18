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
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; } ;
struct kek_mgmt_req {int new_curidx_ksop; int /*<<< orphan*/  tag; } ;
struct inbound_queue_table {int dummy; } ;

/* Variables and functions */
 int KEK_MGMT_SUBOP_KEYCARDUPDATE ; 
 int /*<<< orphan*/  OPC_INB_KEK_MANAGEMENT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kek_mgmt_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int /*<<< orphan*/ ,struct kek_mgmt_req*,int /*<<< orphan*/ ) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm80xx_encrypt_update(struct pm8001_hba_info *pm8001_ha)
{
	struct kek_mgmt_req payload;
	struct inbound_queue_table *circularQ;
	int rc;
	u32 tag;
	u32 opc = OPC_INB_KEK_MANAGEMENT;

	memset(&payload, 0, sizeof(struct kek_mgmt_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc)
		return -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	/* Currently only one key is used. New KEK index is 1.
	 * Current KEK index is 1. Store KEK to NVRAM is 1.
	 */
	payload.new_curidx_ksop = ((1 << 24) | (1 << 16) | (1 << 8) |
					KEK_MGMT_SUBOP_KEYCARDUPDATE);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload, 0);

	return rc;
}