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
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;
struct qla82xx_md_entry_rdrom {int read_addr; int read_data_size; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 scalar_t__ MD_DIRECT_ROM_READ_BASE ; 
 scalar_t__ MD_DIRECT_ROM_WINDOW ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int qla82xx_md_rw_32 (struct qla_hw_data*,scalar_t__,int,int) ; 

__attribute__((used)) static void
qla82xx_minidump_process_rdrom(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, uint32_t **d_ptr)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t r_addr, r_value;
	uint32_t i, loop_cnt;
	struct qla82xx_md_entry_rdrom *rom_hdr;
	uint32_t *data_ptr = *d_ptr;

	rom_hdr = (struct qla82xx_md_entry_rdrom *)entry_hdr;
	r_addr = rom_hdr->read_addr;
	loop_cnt = rom_hdr->read_data_size/sizeof(uint32_t);

	for (i = 0; i < loop_cnt; i++) {
		qla82xx_md_rw_32(ha, MD_DIRECT_ROM_WINDOW,
		    (r_addr & 0xFFFF0000), 1);
		r_value = qla82xx_md_rw_32(ha,
		    MD_DIRECT_ROM_READ_BASE +
		    (r_addr & 0x0000FFFF), 0, 0);
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += sizeof(uint32_t);
	}
	*d_ptr = data_ptr;
}