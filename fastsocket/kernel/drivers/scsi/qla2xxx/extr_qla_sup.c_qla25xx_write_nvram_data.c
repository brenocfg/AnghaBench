#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int flt_region_vpd_nvram; TYPE_1__* isp_ops; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_optrom ) (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_optrom ) (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int QLA_MEMORY_ALLOC_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RMW_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 

int
qla25xx_write_nvram_data(scsi_qla_host_t *vha, uint8_t *buf, uint32_t naddr,
    uint32_t bytes)
{
	struct qla_hw_data *ha = vha->hw;
#define RMW_BUFFER_SIZE	(64 * 1024)
	uint8_t *dbuf;

	dbuf = vmalloc(RMW_BUFFER_SIZE);
	if (!dbuf)
		return QLA_MEMORY_ALLOC_FAILED;
	ha->isp_ops->read_optrom(vha, dbuf, ha->flt_region_vpd_nvram << 2,
	    RMW_BUFFER_SIZE);
	memcpy(dbuf + (naddr << 2), buf, bytes);
	ha->isp_ops->write_optrom(vha, dbuf, ha->flt_region_vpd_nvram << 2,
	    RMW_BUFFER_SIZE);
	vfree(dbuf);

	return QLA_SUCCESS;
}