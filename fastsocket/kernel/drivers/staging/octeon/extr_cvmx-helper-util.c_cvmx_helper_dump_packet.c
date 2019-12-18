#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int offset; } ;
union cvmx_pip_ip_offset {TYPE_2__ s; void* u64; } ;
struct TYPE_13__ {scalar_t__ nip_shf; } ;
union cvmx_pip_gbl_cfg {TYPE_5__ s; void* u64; } ;
struct TYPE_9__ {int /*<<< orphan*/  wqe_pool; } ;
union cvmx_ipd_wqe_fpa_queue {TYPE_1__ s; void* u64; } ;
struct TYPE_14__ {int size; int addr; int back; int /*<<< orphan*/  pool; int /*<<< orphan*/  i; } ;
union cvmx_buf_ptr {TYPE_6__ s; scalar_t__ u64; } ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {scalar_t__ bufs; int ip_offset; int is_v6; int /*<<< orphan*/  not_IP; } ;
struct TYPE_12__ {TYPE_3__ s; } ;
struct TYPE_15__ {scalar_t__ len; union cvmx_buf_ptr packet_ptr; TYPE_4__ word2; int /*<<< orphan*/  packet_data; int /*<<< orphan*/  qos; int /*<<< orphan*/  ipprt; } ;
typedef  TYPE_7__ cvmx_wqe_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IPD_WQE_FPA_QUEUE ; 
 int /*<<< orphan*/  CVMX_PIP_GBL_CFG ; 
 int /*<<< orphan*/  CVMX_PIP_IP_OFFSET ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_phys_to_ptr (int) ; 
 int cvmx_ptr_to_phys (int /*<<< orphan*/ ) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

int cvmx_helper_dump_packet(cvmx_wqe_t *work)
{
	uint64_t count;
	uint64_t remaining_bytes;
	union cvmx_buf_ptr buffer_ptr;
	uint64_t start_of_buffer;
	uint8_t *data_address;
	uint8_t *end_of_data;

	cvmx_dprintf("Packet Length:   %u\n", work->len);
	cvmx_dprintf("    Input Port:  %u\n", work->ipprt);
	cvmx_dprintf("    QoS:         %u\n", work->qos);
	cvmx_dprintf("    Buffers:     %u\n", work->word2.s.bufs);

	if (work->word2.s.bufs == 0) {
		union cvmx_ipd_wqe_fpa_queue wqe_pool;
		wqe_pool.u64 = cvmx_read_csr(CVMX_IPD_WQE_FPA_QUEUE);
		buffer_ptr.u64 = 0;
		buffer_ptr.s.pool = wqe_pool.s.wqe_pool;
		buffer_ptr.s.size = 128;
		buffer_ptr.s.addr = cvmx_ptr_to_phys(work->packet_data);
		if (likely(!work->word2.s.not_IP)) {
			union cvmx_pip_ip_offset pip_ip_offset;
			pip_ip_offset.u64 = cvmx_read_csr(CVMX_PIP_IP_OFFSET);
			buffer_ptr.s.addr +=
			    (pip_ip_offset.s.offset << 3) -
			    work->word2.s.ip_offset;
			buffer_ptr.s.addr += (work->word2.s.is_v6 ^ 1) << 2;
		} else {
			/*
			 * WARNING: This code assumes that the packet
			 * is not RAW. If it was, we would use
			 * PIP_GBL_CFG[RAW_SHF] instead of
			 * PIP_GBL_CFG[NIP_SHF].
			 */
			union cvmx_pip_gbl_cfg pip_gbl_cfg;
			pip_gbl_cfg.u64 = cvmx_read_csr(CVMX_PIP_GBL_CFG);
			buffer_ptr.s.addr += pip_gbl_cfg.s.nip_shf;
		}
	} else
		buffer_ptr = work->packet_ptr;
	remaining_bytes = work->len;

	while (remaining_bytes) {
		start_of_buffer =
		    ((buffer_ptr.s.addr >> 7) - buffer_ptr.s.back) << 7;
		cvmx_dprintf("    Buffer Start:%llx\n",
			     (unsigned long long)start_of_buffer);
		cvmx_dprintf("    Buffer I   : %u\n", buffer_ptr.s.i);
		cvmx_dprintf("    Buffer Back: %u\n", buffer_ptr.s.back);
		cvmx_dprintf("    Buffer Pool: %u\n", buffer_ptr.s.pool);
		cvmx_dprintf("    Buffer Data: %llx\n",
			     (unsigned long long)buffer_ptr.s.addr);
		cvmx_dprintf("    Buffer Size: %u\n", buffer_ptr.s.size);

		cvmx_dprintf("\t\t");
		data_address = (uint8_t *) cvmx_phys_to_ptr(buffer_ptr.s.addr);
		end_of_data = data_address + buffer_ptr.s.size;
		count = 0;
		while (data_address < end_of_data) {
			if (remaining_bytes == 0)
				break;
			else
				remaining_bytes--;
			cvmx_dprintf("%02x", (unsigned int)*data_address);
			data_address++;
			if (remaining_bytes && (count == 7)) {
				cvmx_dprintf("\n\t\t");
				count = 0;
			} else
				count++;
		}
		cvmx_dprintf("\n");

		if (remaining_bytes)
			buffer_ptr = *(union cvmx_buf_ptr *)
				cvmx_phys_to_ptr(buffer_ptr.s.addr - 8);
	}
	return 0;
}