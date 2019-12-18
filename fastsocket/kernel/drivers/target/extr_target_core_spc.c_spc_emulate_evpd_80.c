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
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned char u16 ;
struct TYPE_2__ {char* unit_serial; } ;
struct se_device {int dev_flags; TYPE_1__ t10_wwn; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int DF_EMULATED_VPD_UNIT_SERIAL ; 
 scalar_t__ sprintf (unsigned char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_80(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;
	u16 len = 0;

	if (dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) {
		u32 unit_serial_len;

		unit_serial_len = strlen(dev->t10_wwn.unit_serial);
		unit_serial_len++; /* For NULL Terminator */

		len += sprintf(&buf[4], "%s", dev->t10_wwn.unit_serial);
		len++; /* Extra Byte for NULL Terminator */
		buf[3] = len;
	}
	return 0;
}