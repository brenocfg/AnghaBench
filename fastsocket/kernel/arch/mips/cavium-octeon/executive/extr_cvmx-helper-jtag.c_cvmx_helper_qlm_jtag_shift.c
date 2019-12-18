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
struct TYPE_2__ {int shift; int shft_cnt; int shft_reg; int select; } ;
union cvmx_ciu_qlm_jtgd {TYPE_1__ s; scalar_t__ u64; } ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_QLM_JTGD ; 
 int /*<<< orphan*/  OCTEON_CN56XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

uint32_t cvmx_helper_qlm_jtag_shift(int qlm, int bits, uint32_t data)
{
	union cvmx_ciu_qlm_jtgd jtgd;
	jtgd.u64 = 0;
	jtgd.s.shift = 1;
	jtgd.s.shft_cnt = bits - 1;
	jtgd.s.shft_reg = data;
	if (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		jtgd.s.select = 1 << qlm;
	cvmx_write_csr(CVMX_CIU_QLM_JTGD, jtgd.u64);
	do {
		jtgd.u64 = cvmx_read_csr(CVMX_CIU_QLM_JTGD);
	} while (jtgd.s.shift);
	return jtgd.s.shft_reg >> (32 - bits);
}