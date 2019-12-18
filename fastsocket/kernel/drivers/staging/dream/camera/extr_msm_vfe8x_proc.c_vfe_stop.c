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
typedef  int uint32_t ;
typedef  void* boolean ;
struct TYPE_2__ {scalar_t__ vfebase; void* vfeStatsPingPongReloadFlag; void* vfeStopAckPending; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_HALT ; 
 int /*<<< orphan*/  AXI_HALT_CLEAR ; 
 int AXI_STATUS_BUSY_MASK ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  VFE_CLEAR_ALL_IRQS ; 
 int /*<<< orphan*/  VFE_DISABLE_ALL_IRQS ; 
 int /*<<< orphan*/  VFE_IMASK_WHILE_STOPPING ; 
 scalar_t__ VFE_IRQ_CLEAR ; 
 int /*<<< orphan*/  VFE_RESET_UPON_STOP_CMD ; 
 int /*<<< orphan*/  VFE_TEST_GEN_STOP ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  vfe_camif_stop_immediately () ; 
 int /*<<< orphan*/  vfe_pm_stop () ; 
 int /*<<< orphan*/  vfe_prog_hw_testgen_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_program_axi_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_program_global_reset_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_program_irq_mask (int /*<<< orphan*/ ) ; 
 int vfe_read_axi_status () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void vfe_stop(void)
{
	boolean vfeAxiBusy;
	uint32_t vfeAxiStauts;

	/* for reset hw modules, and send msg when reset_irq comes.*/
	ctrl->vfeStopAckPending = TRUE;

	ctrl->vfeStatsPingPongReloadFlag = FALSE;
	vfe_pm_stop();

	/* disable all interrupts.  */
	vfe_program_irq_mask(VFE_DISABLE_ALL_IRQS);

	/* in either continuous or snapshot mode, stop command can be issued
	 * at any time.
	 */
	vfe_camif_stop_immediately();
	vfe_program_axi_cmd(AXI_HALT);
	vfe_prog_hw_testgen_cmd(VFE_TEST_GEN_STOP);

	vfeAxiBusy = TRUE;

	while (vfeAxiBusy) {
		vfeAxiStauts = vfe_read_axi_status();
		if ((vfeAxiStauts & AXI_STATUS_BUSY_MASK) != 0)
			vfeAxiBusy = FALSE;
	}

	vfe_program_axi_cmd(AXI_HALT_CLEAR);

	/* clear all pending interrupts */
	writel(VFE_CLEAR_ALL_IRQS, ctrl->vfebase + VFE_IRQ_CLEAR);

	/* enable reset_ack and async timer interrupt only while stopping
	 * the pipeline.
	 */
	vfe_program_irq_mask(VFE_IMASK_WHILE_STOPPING);

	vfe_program_global_reset_cmd(VFE_RESET_UPON_STOP_CMD);
}