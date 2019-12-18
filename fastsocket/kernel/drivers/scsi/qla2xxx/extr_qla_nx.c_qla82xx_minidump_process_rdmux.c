#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct qla82xx_md_entry_mux {scalar_t__ read_addr; scalar_t__ select_addr; scalar_t__ select_value_stride; scalar_t__ select_value; scalar_t__ op_count; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 void* cpu_to_le32 (scalar_t__) ; 
 scalar_t__ qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
qla82xx_minidump_process_rdmux(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t r_addr, s_stride, s_addr, s_value, loop_cnt, i, r_value;
	struct qla82xx_md_entry_mux *mux_hdr;
	uint32_t *data_ptr = *d_ptr;

	mux_hdr = (struct qla82xx_md_entry_mux *)entry_hdr;
	r_addr = mux_hdr->read_addr;
	s_addr = mux_hdr->select_addr;
	s_stride = mux_hdr->select_value_stride;
	s_value = mux_hdr->select_value;
	loop_cnt = mux_hdr->op_count;

	for (i = 0; i < loop_cnt; i++) {
		qla82xx_md_rw_32(ha, s_addr, s_value, 1);
		r_value = qla82xx_md_rw_32(ha, r_addr, 0, 0);
		*data_ptr++ = cpu_to_le32(s_value);
		*data_ptr++ = cpu_to_le32(r_value);
		s_value += s_stride;
	}
	*d_ptr = data_ptr;
}