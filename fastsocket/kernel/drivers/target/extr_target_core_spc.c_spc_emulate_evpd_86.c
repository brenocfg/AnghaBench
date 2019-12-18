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
struct se_device {int dummy; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 scalar_t__ spc_check_dev_wce (struct se_device*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_86(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;

	buf[3] = 0x3c;
	/* Set HEADSUP, ORDSUP, SIMPSUP */
	buf[5] = 0x07;

	/* If WriteCache emulation is enabled, set V_SUP */
	if (spc_check_dev_wce(dev))
		buf[6] = 0x01;
	return 0;
}