#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDMA_CSR (int) ; 
 int /*<<< orphan*/  CAMDMA_IRQSTATUS_L0 ; 
 int omap24xxcam_reg_in (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 omap24xxcam_dmahw_ack_ch(unsigned long base, int dmach)
{
	u32 csr;

	csr = omap24xxcam_reg_in(base, CAMDMA_CSR(dmach));
	/* ack interrupt in CSR */
	omap24xxcam_reg_out(base, CAMDMA_CSR(dmach), csr);
	/* ack interrupt in IRQSTATUS */
	omap24xxcam_reg_out(base, CAMDMA_IRQSTATUS_L0, (1 << dmach));

	return csr;
}