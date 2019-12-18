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
typedef  int u16 ;
struct TYPE_8__ {scalar_t__ affil_supp; scalar_t__ affil_valid; } ;
struct smp_resp {scalar_t__ frame_type; scalar_t__ function; scalar_t__ result; TYPE_4__ rps; } ;
struct sas_end_device {scalar_t__ I_T_nexus_loss_timeout; } ;
struct TYPE_7__ {struct smp_resp rps_resp; } ;
struct domain_device {int* sas_addr; scalar_t__ dev_type; int tproto; int pathways; int /*<<< orphan*/  rphy; int /*<<< orphan*/  parent; TYPE_3__ sata_dev; TYPE_2__* port; void* lldd_dev; } ;
struct asd_ha_struct {int dummy; } ;
struct TYPE_6__ {int phy_mask; scalar_t__ oob_mode; TYPE_1__* ha; } ;
struct TYPE_5__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int CONCURRENT_CONN_SUPP ; 
 int CONN_MASK ; 
 int DDB_TARG_FLAGS ; 
 int DDB_TARG_FLAGS2 ; 
 int DDB_TP_CONN_TYPE ; 
 int DEST_SAS_ADDR ; 
 scalar_t__ EDGE_DEV ; 
 int /*<<< orphan*/  EXEC_QUEUE_TAIL ; 
 scalar_t__ FANOUT_DEV ; 
 int /*<<< orphan*/  INIT_CONN_TAG ; 
 int /*<<< orphan*/  ITNL_TIMEOUT ; 
 scalar_t__ ITNL_TIMEOUT_CONST ; 
 int MAX_CCONN ; 
 int NUM_CTX ; 
 int OPEN_REQUIRED ; 
 int SAS_ADDR_SIZE ; 
 scalar_t__ SAS_END_DEV ; 
 int SAS_PROTOCOL_STP ; 
 scalar_t__ SATA_DEV ; 
 int SATA_MULTIPORT ; 
 scalar_t__ SATA_OOB_MODE ; 
 scalar_t__ SATA_PM ; 
 int /*<<< orphan*/  SEND_QUEUE_HEAD ; 
 int /*<<< orphan*/  SEND_QUEUE_TAIL ; 
 int /*<<< orphan*/  SISTER_DDB ; 
 scalar_t__ SMP_REPORT_PHY_SATA ; 
 scalar_t__ SMP_RESPONSE ; 
 scalar_t__ SMP_RESP_FUNC_ACC ; 
 int STP_AFFIL_POL ; 
 int STP_CL_POL_NO_TX ; 
 int SUPPORTS_AFFIL ; 
 int /*<<< orphan*/  asd_ddbsite_write_byte (struct asd_ha_struct*,int,int,int) ; 
 int /*<<< orphan*/  asd_ddbsite_write_word (struct asd_ha_struct*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asd_free_ddb (struct asd_ha_struct*,int) ; 
 int asd_get_ddb (struct asd_ha_struct*) ; 
 int asd_init_sata (struct domain_device*) ; 
 int /*<<< orphan*/  asd_set_ddb_type (struct domain_device*) ; 
 int min (scalar_t__,int) ; 
 struct sas_end_device* rphy_to_end_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_init_target_ddb(struct domain_device *dev)
{
	int ddb, i;
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;
	u8 flags = 0;

	ddb = asd_get_ddb(asd_ha);
	if (ddb < 0)
		return ddb;

	dev->lldd_dev = (void *) (unsigned long) ddb;

	asd_ddbsite_write_byte(asd_ha, ddb, 0, DDB_TP_CONN_TYPE);
	asd_ddbsite_write_byte(asd_ha, ddb, 1, 0);
	asd_ddbsite_write_word(asd_ha, ddb, INIT_CONN_TAG, 0xFFFF);
	for (i = 0; i < SAS_ADDR_SIZE; i++)
		asd_ddbsite_write_byte(asd_ha, ddb, DEST_SAS_ADDR+i,
				       dev->sas_addr[i]);
	asd_ddbsite_write_word(asd_ha, ddb, SEND_QUEUE_HEAD, 0xFFFF);
	asd_set_ddb_type(dev);
	asd_ddbsite_write_byte(asd_ha, ddb, CONN_MASK, dev->port->phy_mask);
	if (dev->port->oob_mode != SATA_OOB_MODE) {
		flags |= OPEN_REQUIRED;
		if ((dev->dev_type == SATA_DEV) ||
		    (dev->tproto & SAS_PROTOCOL_STP)) {
			struct smp_resp *rps_resp = &dev->sata_dev.rps_resp;
			if (rps_resp->frame_type == SMP_RESPONSE &&
			    rps_resp->function == SMP_REPORT_PHY_SATA &&
			    rps_resp->result == SMP_RESP_FUNC_ACC) {
				if (rps_resp->rps.affil_valid)
					flags |= STP_AFFIL_POL;
				if (rps_resp->rps.affil_supp)
					flags |= SUPPORTS_AFFIL;
			}
		} else {
			flags |= CONCURRENT_CONN_SUPP;
			if (!dev->parent &&
			    (dev->dev_type == EDGE_DEV ||
			     dev->dev_type == FANOUT_DEV))
				asd_ddbsite_write_byte(asd_ha, ddb, MAX_CCONN,
						       4);
			else
				asd_ddbsite_write_byte(asd_ha, ddb, MAX_CCONN,
						       dev->pathways);
			asd_ddbsite_write_byte(asd_ha, ddb, NUM_CTX, 1);
		}
	}
	if (dev->dev_type == SATA_PM)
		flags |= SATA_MULTIPORT;
	asd_ddbsite_write_byte(asd_ha, ddb, DDB_TARG_FLAGS, flags);

	flags = 0;
	if (dev->tproto & SAS_PROTOCOL_STP)
		flags |= STP_CL_POL_NO_TX;
	asd_ddbsite_write_byte(asd_ha, ddb, DDB_TARG_FLAGS2, flags);

	asd_ddbsite_write_word(asd_ha, ddb, EXEC_QUEUE_TAIL, 0xFFFF);
	asd_ddbsite_write_word(asd_ha, ddb, SEND_QUEUE_TAIL, 0xFFFF);
	asd_ddbsite_write_word(asd_ha, ddb, SISTER_DDB, 0xFFFF);

	if (dev->dev_type == SATA_DEV || (dev->tproto & SAS_PROTOCOL_STP)) {
		i = asd_init_sata(dev);
		if (i < 0) {
			asd_free_ddb(asd_ha, ddb);
			return i;
		}
	}

	if (dev->dev_type == SAS_END_DEV) {
		struct sas_end_device *rdev = rphy_to_end_device(dev->rphy);
		if (rdev->I_T_nexus_loss_timeout > 0)
			asd_ddbsite_write_word(asd_ha, ddb, ITNL_TIMEOUT,
					       min(rdev->I_T_nexus_loss_timeout,
						   (u16)ITNL_TIMEOUT_CONST));
		else
			asd_ddbsite_write_word(asd_ha, ddb, ITNL_TIMEOUT,
					       (u16)ITNL_TIMEOUT_CONST);
	}
	return 0;
}