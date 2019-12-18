#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  host_ioa_interrupt_reg; } ;
struct pmcraid_instance {int /*<<< orphan*/  ioa_state; TYPE_1__ int_regs; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {unsigned long data; void (* function ) (unsigned long) ;scalar_t__ expires; } ;
struct pmcraid_cmd {TYPE_2__ timer; int /*<<< orphan*/  time_left; struct pmcraid_instance* drv_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOORBELL_IOA_RESET_ALERT ; 
 int /*<<< orphan*/  IOA_STATE_IN_HARD_RESET ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_MEMORY ; 
 scalar_t__ PMCRAID_CHECK_FOR_RESET_TIMEOUT ; 
 int /*<<< orphan*/  PMCRAID_RESET_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pmcraid_info (char*,...) ; 
 scalar_t__ pmcraid_reset_alert_done ; 
 int /*<<< orphan*/  pmcraid_start_bist (struct pmcraid_cmd*) ; 

__attribute__((used)) static void pmcraid_reset_alert(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	u32 doorbells;
	int rc;
	u16 pci_reg;

	/* If we are able to access IOA PCI config space, alert IOA that we are
	 * going to reset it soon. This enables IOA to preserv persistent error
	 * data if any. In case memory space is not accessible, proceed with
	 * BIST or slot_reset
	 */
	rc = pci_read_config_word(pinstance->pdev, PCI_COMMAND, &pci_reg);
	if ((rc == PCIBIOS_SUCCESSFUL) && (pci_reg & PCI_COMMAND_MEMORY)) {

		/* wait for IOA permission i.e until CRITICAL_OPERATION bit is
		 * reset IOA doesn't generate any interrupts when CRITICAL
		 * OPERATION bit is reset. A timer is started to wait for this
		 * bit to be reset.
		 */
		cmd->time_left = PMCRAID_RESET_TIMEOUT;
		cmd->timer.data = (unsigned long)cmd;
		cmd->timer.expires = jiffies + PMCRAID_CHECK_FOR_RESET_TIMEOUT;
		cmd->timer.function =
			(void (*)(unsigned long))pmcraid_reset_alert_done;
		add_timer(&cmd->timer);

		iowrite32(DOORBELL_IOA_RESET_ALERT,
			pinstance->int_regs.host_ioa_interrupt_reg);
		doorbells =
			ioread32(pinstance->int_regs.host_ioa_interrupt_reg);
		pmcraid_info("doorbells after reset alert: %x\n", doorbells);
	} else {
		pmcraid_info("PCI config is not accessible starting BIST\n");
		pinstance->ioa_state = IOA_STATE_IN_HARD_RESET;
		pmcraid_start_bist(cmd);
	}
}