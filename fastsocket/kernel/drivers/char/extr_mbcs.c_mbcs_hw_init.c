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
union cm_req_timeout {int cm_req_timeout_reg; int /*<<< orphan*/  time_out; } ;
union cm_control {int cm_control_reg; int rearm_stat_regs; int alg_clr; int wr_dma_clr; int rd_dma_clr; } ;
typedef  int uint64_t ;
struct mbcs_soft {void* mmr_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBCS_CM_CLR_ERR_STAT ; 
 int /*<<< orphan*/  MBCS_CM_CONTROL ; 
 int /*<<< orphan*/  MBCS_CM_CONTROL_REQ_TOUT_MASK ; 
 int /*<<< orphan*/  MBCS_CM_ERROR_DETAIL1 ; 
 int /*<<< orphan*/  MBCS_CM_ERR_INT_EN ; 
 int /*<<< orphan*/  MBCS_CM_ERR_STAT ; 
 int /*<<< orphan*/  MBCS_CM_REQ_TOUT ; 
 void* MBCS_MMR_GET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBCS_MMR_SET (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MBCS_MMR_ZERO (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbcs_debug_pioaddr_set (struct mbcs_soft*) ; 
 int /*<<< orphan*/  mbcs_gscr_pioaddr_set (struct mbcs_soft*) ; 

__attribute__((used)) static inline int mbcs_hw_init(struct mbcs_soft *soft)
{
	void *mmr_base = soft->mmr_base;
	union cm_control cm_control;
	union cm_req_timeout cm_req_timeout;
	uint64_t err_stat;

	cm_req_timeout.cm_req_timeout_reg =
	    MBCS_MMR_GET(mmr_base, MBCS_CM_REQ_TOUT);

	cm_req_timeout.time_out = MBCS_CM_CONTROL_REQ_TOUT_MASK;
	MBCS_MMR_SET(mmr_base, MBCS_CM_REQ_TOUT,
		     cm_req_timeout.cm_req_timeout_reg);

	mbcs_gscr_pioaddr_set(soft);
	mbcs_debug_pioaddr_set(soft);

	/* clear errors */
	err_stat = MBCS_MMR_GET(mmr_base, MBCS_CM_ERR_STAT);
	MBCS_MMR_SET(mmr_base, MBCS_CM_CLR_ERR_STAT, err_stat);
	MBCS_MMR_ZERO(mmr_base, MBCS_CM_ERROR_DETAIL1);

	/* enable interrupts */
	/* turn off 2^23 (INT_EN_PIO_REQ_ADDR_INV) */
	MBCS_MMR_SET(mmr_base, MBCS_CM_ERR_INT_EN, 0x3ffffff7e00ffUL);

	/* arm status regs and clear engines */
	cm_control.cm_control_reg = MBCS_MMR_GET(mmr_base, MBCS_CM_CONTROL);
	cm_control.rearm_stat_regs = 1;
	cm_control.alg_clr = 1;
	cm_control.wr_dma_clr = 1;
	cm_control.rd_dma_clr = 1;

	MBCS_MMR_SET(mmr_base, MBCS_CM_CONTROL, cm_control.cm_control_reg);

	return 0;
}