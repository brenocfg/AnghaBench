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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int qla82xx_device_state_handler (int /*<<< orphan*/ *) ; 

int
qla82xx_load_risc(scsi_qla_host_t *vha, uint32_t *srisc_addr)
{
	int rval;
	rval = qla82xx_device_state_handler(vha);
	return rval;
}