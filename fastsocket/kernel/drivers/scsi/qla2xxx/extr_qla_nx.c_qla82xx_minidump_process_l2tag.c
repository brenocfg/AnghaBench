#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_9__ {scalar_t__ init_tag_value; scalar_t__ tag_value_stride; } ;
struct TYPE_8__ {scalar_t__ read_addr_cnt; scalar_t__ read_addr_stride; } ;
struct TYPE_7__ {scalar_t__ write_value; unsigned long poll_wait; unsigned long poll_mask; } ;
struct qla82xx_md_entry_cache {scalar_t__ op_count; scalar_t__ read_addr; scalar_t__ control_addr; scalar_t__ tag_reg_addr; TYPE_3__ addr_ctrl; TYPE_2__ read_ctrl; TYPE_1__ cache_ctrl; } ;
struct TYPE_10__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_4__*,int,char*,scalar_t__,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 scalar_t__ qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int
qla82xx_minidump_process_l2tag(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t addr, r_addr, c_addr, t_r_addr;
	uint32_t i, k, loop_count, t_value, r_cnt, r_value;
	unsigned long p_wait, w_time, p_mask;
	uint32_t c_value_w, c_value_r;
	struct qla82xx_md_entry_cache *cache_hdr;
	int rval = QLA_FUNCTION_FAILED;
	uint32_t *data_ptr = *d_ptr;

	cache_hdr = (struct qla82xx_md_entry_cache *)entry_hdr;
	loop_count = cache_hdr->op_count;
	r_addr = cache_hdr->read_addr;
	c_addr = cache_hdr->control_addr;
	c_value_w = cache_hdr->cache_ctrl.write_value;

	t_r_addr = cache_hdr->tag_reg_addr;
	t_value = cache_hdr->addr_ctrl.init_tag_value;
	r_cnt = cache_hdr->read_ctrl.read_addr_cnt;
	p_wait = cache_hdr->cache_ctrl.poll_wait;
	p_mask = cache_hdr->cache_ctrl.poll_mask;

	for (i = 0; i < loop_count; i++) {
		qla82xx_md_rw_32(ha, t_r_addr, t_value, 1);
		if (c_value_w)
			qla82xx_md_rw_32(ha, c_addr, c_value_w, 1);

		if (p_mask) {
			w_time = jiffies + p_wait;
			do {
				c_value_r = qla82xx_md_rw_32(ha, c_addr, 0, 0);
				if ((c_value_r & p_mask) == 0)
					break;
				else if (time_after_eq(jiffies, w_time)) {
					/* capturing dump failed */
					ql_dbg(ql_dbg_p3p, vha, 0xb032,
					    "c_value_r: 0x%x, poll_mask: 0x%lx,"
					    " w_time: 0x%lx\n",
					    c_value_r, p_mask, w_time);
					return rval;
				}
			} while (1);
		}

		addr = r_addr;
		for (k = 0; k < r_cnt; k++) {
			r_value = qla82xx_md_rw_32(ha, addr, 0, 0);
			*data_ptr++ = cpu_to_le32(r_value);
			addr += cache_hdr->read_ctrl.read_addr_stride;
		}
		t_value += cache_hdr->addr_ctrl.tag_value_stride;
	}
	*d_ptr = data_ptr;
	return QLA_SUCCESS;
}