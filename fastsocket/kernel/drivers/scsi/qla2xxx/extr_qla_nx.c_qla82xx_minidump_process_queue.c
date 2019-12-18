#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_6__ {scalar_t__ queue_id_stride; } ;
struct TYPE_5__ {scalar_t__ read_addr_cnt; scalar_t__ read_addr_stride; } ;
struct qla82xx_md_entry_queue {scalar_t__ select_addr; scalar_t__ op_count; scalar_t__ read_addr; TYPE_2__ q_strd; TYPE_1__ rd_strd; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
qla82xx_minidump_process_queue(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t s_addr, r_addr;
	uint32_t r_stride, r_value, r_cnt, qid = 0;
	uint32_t i, k, loop_cnt;
	struct qla82xx_md_entry_queue *q_hdr;
	uint32_t *data_ptr = *d_ptr;

	q_hdr = (struct qla82xx_md_entry_queue *)entry_hdr;
	s_addr = q_hdr->select_addr;
	r_cnt = q_hdr->rd_strd.read_addr_cnt;
	r_stride = q_hdr->rd_strd.read_addr_stride;
	loop_cnt = q_hdr->op_count;

	for (i = 0; i < loop_cnt; i++) {
		qla82xx_md_rw_32(ha, s_addr, qid, 1);
		r_addr = q_hdr->read_addr;
		for (k = 0; k < r_cnt; k++) {
			r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
			*data_ptr++ = cpu_to_le32(r_value);
			r_addr += r_stride;
		}
		qid += q_hdr->q_strd.queue_id_stride;
	}
	*d_ptr = data_ptr;
}