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

/* Variables and functions */
 int /*<<< orphan*/  CAMDMA_CCR (int) ; 
 int /*<<< orphan*/  CAMDMA_CCR_ENABLE ; 
 int /*<<< orphan*/  CAMDMA_CICR (int) ; 
 int /*<<< orphan*/  CAMDMA_CLNK_CTRL (int) ; 
 int /*<<< orphan*/  CAMDMA_CLNK_CTRL_ENABLE_LNK ; 
 int /*<<< orphan*/  omap24xxcam_reg_merge (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap24xxcam_dmahw_abort_ch(unsigned long base, int dmach)
{
	/* mask all interrupts from this channel */
	omap24xxcam_reg_out(base, CAMDMA_CICR(dmach), 0);
	/* unlink this channel */
	omap24xxcam_reg_merge(base, CAMDMA_CLNK_CTRL(dmach), 0,
			      CAMDMA_CLNK_CTRL_ENABLE_LNK);
	/* disable this channel */
	omap24xxcam_reg_merge(base, CAMDMA_CCR(dmach), 0, CAMDMA_CCR_ENABLE);
}