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
struct se_lun {int /*<<< orphan*/  lun_sep; } ;
struct TYPE_4__ {char* model; char* revision; } ;
struct se_device {TYPE_2__ t10_wwn; TYPE_1__* transport; } ;
struct se_cmd {struct se_device* se_dev; struct se_lun* se_lun; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_3__ {scalar_t__ (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 scalar_t__ TYPE_TAPE ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,...) ; 
 int /*<<< orphan*/  spc_fill_alua_data (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ stub1 (struct se_device*) ; 

sense_reason_t
spc_emulate_inquiry_std(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_lun *lun = cmd->se_lun;
	struct se_device *dev = cmd->se_dev;

	/* Set RMB (removable media) for tape devices */
	if (dev->transport->get_device_type(dev) == TYPE_TAPE)
		buf[1] = 0x80;

	buf[2] = 0x05; /* SPC-3 */

	/*
	 * NORMACA and HISUP = 0, RESPONSE DATA FORMAT = 2
	 *
	 * SPC4 says:
	 *   A RESPONSE DATA FORMAT field set to 2h indicates that the
	 *   standard INQUIRY data is in the format defined in this
	 *   standard. Response data format values less than 2h are
	 *   obsolete. Response data format values greater than 2h are
	 *   reserved.
	 */
	buf[3] = 2;

	/*
	 * Enable SCCS and TPGS fields for Emulated ALUA
	 */
	spc_fill_alua_data(lun->lun_sep, buf);

	buf[7] = 0x2; /* CmdQue=1 */

	snprintf(&buf[8], 8, "LIO-ORG");
	snprintf(&buf[16], 16, "%s", dev->t10_wwn.model);
	snprintf(&buf[32], 4, "%s", dev->t10_wwn.revision);
	buf[4] = 31; /* Set additional length to 31 */

	return 0;
}