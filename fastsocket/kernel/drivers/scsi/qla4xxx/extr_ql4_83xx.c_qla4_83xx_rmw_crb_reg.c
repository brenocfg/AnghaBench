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
typedef  int uint32_t ;
struct TYPE_2__ {int* array; } ;
struct scsi_qla_host {TYPE_1__ reset_tmplt; } ;
struct qla4_83xx_rmw {int index_a; int test_mask; int shl; int shr; int or_value; int xor_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4_83xx_rd_reg_indirect (struct scsi_qla_host*,int,int*) ; 
 int /*<<< orphan*/  qla4_83xx_wr_reg_indirect (struct scsi_qla_host*,int,int) ; 

__attribute__((used)) static void qla4_83xx_rmw_crb_reg(struct scsi_qla_host *ha, uint32_t raddr,
				  uint32_t waddr,
				  struct qla4_83xx_rmw *p_rmw_hdr)
{
	uint32_t value;

	if (p_rmw_hdr->index_a)
		value = ha->reset_tmplt.array[p_rmw_hdr->index_a];
	else
		qla4_83xx_rd_reg_indirect(ha, raddr, &value);

	value &= p_rmw_hdr->test_mask;
	value <<= p_rmw_hdr->shl;
	value >>= p_rmw_hdr->shr;
	value |= p_rmw_hdr->or_value;
	value ^= p_rmw_hdr->xor_value;

	qla4_83xx_wr_reg_indirect(ha, waddr, value);

	return;
}