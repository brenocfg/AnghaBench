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
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBX_TOV_SECONDS ; 
 int qla2x00_issue_iocb_timeout (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

int
qla2x00_issue_iocb(scsi_qla_host_t *vha, void *buffer, dma_addr_t phys_addr,
    size_t size)
{
	return qla2x00_issue_iocb_timeout(vha, buffer, phys_addr, size,
	    MBX_TOV_SECONDS);
}