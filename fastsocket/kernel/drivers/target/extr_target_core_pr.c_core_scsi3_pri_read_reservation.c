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
typedef  int u64 ;
typedef  int u32 ;
struct t10_pr_registration {int pr_res_type; int pr_res_key; int pr_res_scope; } ;
struct TYPE_2__ {int pr_generation; } ;
struct se_device {int /*<<< orphan*/  dev_reservation_lock; struct t10_pr_registration* dev_pr_res_holder; TYPE_1__ t10_pr; } ;
struct se_cmd {int data_length; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int PR_TYPE_EXCLUSIVE_ACCESS_ALLREG ; 
 int PR_TYPE_WRITE_EXCLUSIVE_ALLREG ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

__attribute__((used)) static sense_reason_t
core_scsi3_pri_read_reservation(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct t10_pr_registration *pr_reg;
	unsigned char *buf;
	u64 pr_res_key;
	u32 add_len = 16; /* Hardcoded to 16 when a reservation is held. */

	if (cmd->data_length < 8) {
		pr_err("PRIN SA READ_RESERVATIONS SCSI Data Length: %u"
			" too small\n", cmd->data_length);
		return TCM_INVALID_CDB_FIELD;
	}

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	buf[0] = ((dev->t10_pr.pr_generation >> 24) & 0xff);
	buf[1] = ((dev->t10_pr.pr_generation >> 16) & 0xff);
	buf[2] = ((dev->t10_pr.pr_generation >> 8) & 0xff);
	buf[3] = (dev->t10_pr.pr_generation & 0xff);

	spin_lock(&dev->dev_reservation_lock);
	pr_reg = dev->dev_pr_res_holder;
	if (pr_reg) {
		/*
		 * Set the hardcoded Additional Length
		 */
		buf[4] = ((add_len >> 24) & 0xff);
		buf[5] = ((add_len >> 16) & 0xff);
		buf[6] = ((add_len >> 8) & 0xff);
		buf[7] = (add_len & 0xff);

		if (cmd->data_length < 22)
			goto err;

		/*
		 * Set the Reservation key.
		 *
		 * From spc4r17, section 5.7.10:
		 * A persistent reservation holder has its reservation key
		 * returned in the parameter data from a PERSISTENT
		 * RESERVE IN command with READ RESERVATION service action as
		 * follows:
		 * a) For a persistent reservation of the type Write Exclusive
		 *    - All Registrants or Exclusive Access ­ All Regitrants,
		 *      the reservation key shall be set to zero; or
		 * b) For all other persistent reservation types, the
		 *    reservation key shall be set to the registered
		 *    reservation key for the I_T nexus that holds the
		 *    persistent reservation.
		 */
		if ((pr_reg->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
		    (pr_reg->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG))
			pr_res_key = 0;
		else
			pr_res_key = pr_reg->pr_res_key;

		buf[8] = ((pr_res_key >> 56) & 0xff);
		buf[9] = ((pr_res_key >> 48) & 0xff);
		buf[10] = ((pr_res_key >> 40) & 0xff);
		buf[11] = ((pr_res_key >> 32) & 0xff);
		buf[12] = ((pr_res_key >> 24) & 0xff);
		buf[13] = ((pr_res_key >> 16) & 0xff);
		buf[14] = ((pr_res_key >> 8) & 0xff);
		buf[15] = (pr_res_key & 0xff);
		/*
		 * Set the SCOPE and TYPE
		 */
		buf[21] = (pr_reg->pr_res_scope & 0xf0) |
			  (pr_reg->pr_res_type & 0x0f);
	}

err:
	spin_unlock(&dev->dev_reservation_lock);
	transport_kunmap_data_sg(cmd);

	return 0;
}