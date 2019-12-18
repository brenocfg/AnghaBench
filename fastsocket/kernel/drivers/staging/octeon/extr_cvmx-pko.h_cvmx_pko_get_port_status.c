#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* index; } ;
union cvmx_pko_reg_read_idx {void* u64; TYPE_4__ s; } ;
struct TYPE_10__ {int /*<<< orphan*/  doorbell; } ;
union cvmx_pko_mem_debug9 {TYPE_3__ cn38xx; void* u64; } ;
struct TYPE_12__ {int /*<<< orphan*/  doorbell; } ;
union cvmx_pko_mem_debug8 {TYPE_5__ cn58xx; void* u64; } ;
struct TYPE_9__ {void* count; } ;
union cvmx_pko_mem_count1 {void* u64; TYPE_2__ s; } ;
struct TYPE_8__ {void* count; } ;
union cvmx_pko_mem_count0 {void* u64; TYPE_1__ s; } ;
typedef  void* uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  doorbell; void* octets; void* packets; } ;
typedef  TYPE_6__ cvmx_pko_port_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PKO_MEM_COUNT0 ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_COUNT1 ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_DEBUG8 ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_DEBUG9 ; 
 int /*<<< orphan*/  CVMX_PKO_REG_READ_IDX ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* cvmx_pko_get_base_queue (void*) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void cvmx_pko_get_port_status(uint64_t port_num, uint64_t clear,
					    cvmx_pko_port_status_t *status)
{
	union cvmx_pko_reg_read_idx pko_reg_read_idx;
	union cvmx_pko_mem_count0 pko_mem_count0;
	union cvmx_pko_mem_count1 pko_mem_count1;

	pko_reg_read_idx.u64 = 0;
	pko_reg_read_idx.s.index = port_num;
	cvmx_write_csr(CVMX_PKO_REG_READ_IDX, pko_reg_read_idx.u64);

	pko_mem_count0.u64 = cvmx_read_csr(CVMX_PKO_MEM_COUNT0);
	status->packets = pko_mem_count0.s.count;
	if (clear) {
		pko_mem_count0.s.count = port_num;
		cvmx_write_csr(CVMX_PKO_MEM_COUNT0, pko_mem_count0.u64);
	}

	pko_mem_count1.u64 = cvmx_read_csr(CVMX_PKO_MEM_COUNT1);
	status->octets = pko_mem_count1.s.count;
	if (clear) {
		pko_mem_count1.s.count = port_num;
		cvmx_write_csr(CVMX_PKO_MEM_COUNT1, pko_mem_count1.u64);
	}

	if (OCTEON_IS_MODEL(OCTEON_CN3XXX)) {
		union cvmx_pko_mem_debug9 debug9;
		pko_reg_read_idx.s.index = cvmx_pko_get_base_queue(port_num);
		cvmx_write_csr(CVMX_PKO_REG_READ_IDX, pko_reg_read_idx.u64);
		debug9.u64 = cvmx_read_csr(CVMX_PKO_MEM_DEBUG9);
		status->doorbell = debug9.cn38xx.doorbell;
	} else {
		union cvmx_pko_mem_debug8 debug8;
		pko_reg_read_idx.s.index = cvmx_pko_get_base_queue(port_num);
		cvmx_write_csr(CVMX_PKO_REG_READ_IDX, pko_reg_read_idx.u64);
		debug8.u64 = cvmx_read_csr(CVMX_PKO_MEM_DEBUG8);
		status->doorbell = debug8.cn58xx.doorbell;
	}
}