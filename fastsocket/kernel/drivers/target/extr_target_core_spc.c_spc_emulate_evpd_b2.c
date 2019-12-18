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
struct TYPE_3__ {scalar_t__ emulate_tpu; scalar_t__ emulate_tpws; } ;
struct se_device {TYPE_1__ dev_attrib; TYPE_2__* transport; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_4__ {unsigned char (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 unsigned char stub1 (struct se_device*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_b2(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;

	/*
	 * From spc3r22 section 6.5.4 Thin Provisioning VPD page:
	 *
	 * The PAGE LENGTH field is defined in SPC-4. If the DP bit is set to
	 * zero, then the page length shall be set to 0004h.  If the DP bit
	 * is set to one, then the page length shall be set to the value
	 * defined in table 162.
	 */
	buf[0] = dev->transport->get_device_type(dev);

	/*
	 * Set Hardcoded length mentioned above for DP=0
	 */
	put_unaligned_be16(0x0004, &buf[2]);

	/*
	 * The THRESHOLD EXPONENT field indicates the threshold set size in
	 * LBAs as a power of 2 (i.e., the threshold set size is equal to
	 * 2(threshold exponent)).
	 *
	 * Note that this is currently set to 0x00 as mkp says it will be
	 * changing again.  We can enable this once it has settled in T10
	 * and is actually used by Linux/SCSI ML code.
	 */
	buf[4] = 0x00;

	/*
	 * A TPU bit set to one indicates that the device server supports
	 * the UNMAP command (see 5.25). A TPU bit set to zero indicates
	 * that the device server does not support the UNMAP command.
	 */
	if (dev->dev_attrib.emulate_tpu != 0)
		buf[5] = 0x80;

	/*
	 * A TPWS bit set to one indicates that the device server supports
	 * the use of the WRITE SAME (16) command (see 5.42) to unmap LBAs.
	 * A TPWS bit set to zero indicates that the device server does not
	 * support the use of the WRITE SAME (16) command to unmap LBAs.
	 */
	if (dev->dev_attrib.emulate_tpws != 0)
		buf[5] |= 0x40;

	return 0;
}