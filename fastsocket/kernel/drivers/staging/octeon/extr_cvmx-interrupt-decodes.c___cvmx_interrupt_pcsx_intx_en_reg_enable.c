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
struct TYPE_2__ {int sync_bad_en; int an_bad_en; int rxlock_en; int rxbad_en; int txbad_en; int txfifo_en; int txfifu_en; int an_err_en; } ;
union cvmx_pcsx_intx_en_reg {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PCSX_INTX_EN_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_INTX_REG (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void __cvmx_interrupt_pcsx_intx_en_reg_enable(int index, int block)
{
	union cvmx_pcsx_intx_en_reg pcs_int_en_reg;
	cvmx_write_csr(CVMX_PCSX_INTX_REG(index, block),
		       cvmx_read_csr(CVMX_PCSX_INTX_REG(index, block)));
	pcs_int_en_reg.u64 = 0;
	if (OCTEON_IS_MODEL(OCTEON_CN56XX)) {
		/* Skipping pcs_int_en_reg.s.reserved_12_63 */
		/*pcs_int_en_reg.s.dup = 1; // This happens during normal operation */
		pcs_int_en_reg.s.sync_bad_en = 1;
		pcs_int_en_reg.s.an_bad_en = 1;
		pcs_int_en_reg.s.rxlock_en = 1;
		pcs_int_en_reg.s.rxbad_en = 1;
		/*pcs_int_en_reg.s.rxerr_en = 1; // This happens during normal operation */
		pcs_int_en_reg.s.txbad_en = 1;
		pcs_int_en_reg.s.txfifo_en = 1;
		pcs_int_en_reg.s.txfifu_en = 1;
		pcs_int_en_reg.s.an_err_en = 1;
		/*pcs_int_en_reg.s.xmit_en = 1; // This happens during normal operation */
		/*pcs_int_en_reg.s.lnkspd_en = 1; // This happens during normal operation */
	}
	if (OCTEON_IS_MODEL(OCTEON_CN52XX)) {
		/* Skipping pcs_int_en_reg.s.reserved_12_63 */
		/*pcs_int_en_reg.s.dup = 1; // This happens during normal operation */
		pcs_int_en_reg.s.sync_bad_en = 1;
		pcs_int_en_reg.s.an_bad_en = 1;
		pcs_int_en_reg.s.rxlock_en = 1;
		pcs_int_en_reg.s.rxbad_en = 1;
		/*pcs_int_en_reg.s.rxerr_en = 1; // This happens during normal operation */
		pcs_int_en_reg.s.txbad_en = 1;
		pcs_int_en_reg.s.txfifo_en = 1;
		pcs_int_en_reg.s.txfifu_en = 1;
		pcs_int_en_reg.s.an_err_en = 1;
		/*pcs_int_en_reg.s.xmit_en = 1; // This happens during normal operation */
		/*pcs_int_en_reg.s.lnkspd_en = 1; // This happens during normal operation */
	}
	cvmx_write_csr(CVMX_PCSX_INTX_EN_REG(index, block), pcs_int_en_reg.u64);
}