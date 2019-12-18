#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_QLA81XX (int /*<<< orphan*/ ) ; 
 int QLA_SUCCESS ; 
 int qla81xx_write_mpi_register (TYPE_1__*,int*) ; 

__attribute__((used)) static int
qla81xx_reset_mpi(scsi_qla_host_t *vha)
{
	uint16_t mb[4] = {0x1010, 0, 1, 0};

	if (!IS_QLA81XX(vha->hw))
	    return QLA_SUCCESS;

	return qla81xx_write_mpi_register(vha, mb);
}