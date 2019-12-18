#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct req_que {int /*<<< orphan*/  dma; scalar_t__ ring; } ;
struct qla_hw_data {int fw_transfer_size; struct req_que** req_q_map; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int FA_RISC_CODE_SEGMENTS ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  qla24xx_read_flash_data (TYPE_1__*,int*,int,int) ; 
 int qla2x00_load_ram (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int swab32 (int) ; 

__attribute__((used)) static int
qla24xx_load_risc_flash(scsi_qla_host_t *vha, uint32_t *srisc_addr,
    uint32_t faddr)
{
	int	rval = QLA_SUCCESS;
	int	segments, fragment;
	uint32_t *dcode, dlen;
	uint32_t risc_addr;
	uint32_t risc_size;
	uint32_t i;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "FW: Loading firmware from flash (%x).\n", faddr);

	rval = QLA_SUCCESS;

	segments = FA_RISC_CODE_SEGMENTS;
	dcode = (uint32_t *)req->ring;
	*srisc_addr = 0;

	/* Validate firmware image by checking version. */
	qla24xx_read_flash_data(vha, dcode, faddr + 4, 4);
	for (i = 0; i < 4; i++)
		dcode[i] = be32_to_cpu(dcode[i]);
	if ((dcode[0] == 0xffffffff && dcode[1] == 0xffffffff &&
	    dcode[2] == 0xffffffff && dcode[3] == 0xffffffff) ||
	    (dcode[0] == 0 && dcode[1] == 0 && dcode[2] == 0 &&
		dcode[3] == 0)) {
		ql_log(ql_log_fatal, vha, 0x008c,
		    "Unable to verify the integrity of flash firmware "
		    "image.\n");
		ql_log(ql_log_fatal, vha, 0x008d,
		    "Firmware data: %08x %08x %08x %08x.\n",
		    dcode[0], dcode[1], dcode[2], dcode[3]);

		return QLA_FUNCTION_FAILED;
	}

	while (segments && rval == QLA_SUCCESS) {
		/* Read segment's load information. */
		qla24xx_read_flash_data(vha, dcode, faddr, 4);

		risc_addr = be32_to_cpu(dcode[2]);
		*srisc_addr = *srisc_addr == 0 ? risc_addr : *srisc_addr;
		risc_size = be32_to_cpu(dcode[3]);

		fragment = 0;
		while (risc_size > 0 && rval == QLA_SUCCESS) {
			dlen = (uint32_t)(ha->fw_transfer_size >> 2);
			if (dlen > risc_size)
				dlen = risc_size;

			ql_dbg(ql_dbg_init, vha, 0x008e,
			    "Loading risc segment@ risc addr %x "
			    "number of dwords 0x%x offset 0x%x.\n",
			    risc_addr, dlen, faddr);

			qla24xx_read_flash_data(vha, dcode, faddr, dlen);
			for (i = 0; i < dlen; i++)
				dcode[i] = swab32(dcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr,
			    dlen);
			if (rval) {
				ql_log(ql_log_fatal, vha, 0x008f,
				    "Failed to load segment %d of firmware.\n",
				    fragment);
				break;
			}

			faddr += dlen;
			risc_addr += dlen;
			risc_size -= dlen;
			fragment++;
		}

		/* Next segment. */
		segments--;
	}

	return rval;
}