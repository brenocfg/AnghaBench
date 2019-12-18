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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct msm_adsp_module {scalar_t__ state; int /*<<< orphan*/  num_commands; int /*<<< orphan*/  id; int /*<<< orphan*/  name; struct adsp_info* info; } ;
struct adsp_info {int /*<<< orphan*/  send_irq; int /*<<< orphan*/  write_ctrl; } ;

/* Variables and functions */
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_CMD_M ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_CMD_WRITE_DONE_V ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_DSP_ADDR_M ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_M ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_NAVAIL_V ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_NO_ERR_V ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_READY_M ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_READY_V ; 
 scalar_t__ ADSP_RTOS_WRITE_CTRL_WORD_STATUS_M ; 
 scalar_t__ ADSP_STATE_ENABLED ; 
 int EAGAIN ; 
 int EIO ; 
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ MSM_AD5_BASE ; 
 scalar_t__ QDSP_RAMC_OFFSET ; 
 int /*<<< orphan*/  adsp_cmd_lock ; 
 scalar_t__ adsp_get_queue_offset (struct adsp_info*,unsigned int) ; 
 scalar_t__ adsp_validate_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int __msm_adsp_write(struct msm_adsp_module *module, unsigned dsp_queue_addr,
		   void *cmd_buf, size_t cmd_size)
{
	uint32_t ctrl_word;
	uint32_t dsp_q_addr;
	uint32_t dsp_addr;
	uint32_t cmd_id = 0;
	int cnt = 0;
	int ret_status = 0;
	unsigned long flags;
	struct adsp_info *info = module->info;

	spin_lock_irqsave(&adsp_cmd_lock, flags);

	if (module->state != ADSP_STATE_ENABLED) {
		spin_unlock_irqrestore(&adsp_cmd_lock, flags);
		pr_err("adsp: module %s not enabled before write\n",
		       module->name);
		return -ENODEV;
	}
	if (adsp_validate_module(module->id)) {
		spin_unlock_irqrestore(&adsp_cmd_lock, flags);
		pr_info("adsp: module id validation failed %s  %d\n",
			module->name, module->id);
		return -ENXIO;
	}
	dsp_q_addr = adsp_get_queue_offset(info, dsp_queue_addr);
	dsp_q_addr &= ADSP_RTOS_WRITE_CTRL_WORD_DSP_ADDR_M;

	/* Poll until the ADSP is ready to accept a command.
	 * Wait for 100us, return error if it's not responding.
	 * If this returns an error, we need to disable ALL modules and
	 * then retry.
	 */
	while (((ctrl_word = readl(info->write_ctrl)) &
		ADSP_RTOS_WRITE_CTRL_WORD_READY_M) !=
		ADSP_RTOS_WRITE_CTRL_WORD_READY_V) {
		if (cnt > 100) {
			pr_err("adsp: timeout waiting for DSP write ready\n");
			ret_status = -EIO;
			goto fail;
		}
		pr_warning("adsp: waiting for DSP write ready\n");
		udelay(1);
		cnt++;
	}

	/* Set the mutex bits */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_M);
	ctrl_word |=  ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_NAVAIL_V;

	/* Clear the command bits */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_CMD_M);

	/* Set the queue address bits */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_DSP_ADDR_M);
	ctrl_word |= dsp_q_addr;

	writel(ctrl_word, info->write_ctrl);

	/* Generate an interrupt to the DSP.  This notifies the DSP that
	 * we are about to send a command on this particular queue.  The
	 * DSP will in response change its state.
	 */
	writel(1, info->send_irq);

	/* Poll until the adsp responds to the interrupt; this does not
	 * generate an interrupt from the adsp.  This should happen within
	 * 5ms.
	 */
	cnt = 0;
	while ((readl(info->write_ctrl) &
		ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_M) ==
		ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_NAVAIL_V) {
		if (cnt > 5000) {
			pr_err("adsp: timeout waiting for adsp ack\n");
			ret_status = -EIO;
			goto fail;
		}
		udelay(1);
		cnt++;
	}

	/* Read the ctrl word */
	ctrl_word = readl(info->write_ctrl);

	if ((ctrl_word & ADSP_RTOS_WRITE_CTRL_WORD_STATUS_M) !=
			 ADSP_RTOS_WRITE_CTRL_WORD_NO_ERR_V) {
		ret_status = -EAGAIN;
		goto fail;
	}

	/* Ctrl word status bits were 00, no error in the ctrl word */

	/* Get the DSP buffer address */
	dsp_addr = (ctrl_word & ADSP_RTOS_WRITE_CTRL_WORD_DSP_ADDR_M) +
		   (uint32_t)MSM_AD5_BASE;

	if (dsp_addr < (uint32_t)(MSM_AD5_BASE + QDSP_RAMC_OFFSET)) {
		uint16_t *buf_ptr = (uint16_t *) cmd_buf;
		uint16_t *dsp_addr16 = (uint16_t *)dsp_addr;
		cmd_size /= sizeof(uint16_t);

		/* Save the command ID */
		cmd_id = (uint32_t) buf_ptr[0];

		/* Copy the command to DSP memory */
		cmd_size++;
		while (--cmd_size)
			*dsp_addr16++ = *buf_ptr++;
	} else {
		uint32_t *buf_ptr = (uint32_t *) cmd_buf;
		uint32_t *dsp_addr32 = (uint32_t *)dsp_addr;
		cmd_size /= sizeof(uint32_t);

		/* Save the command ID */
		cmd_id = buf_ptr[0];

		cmd_size++;
		while (--cmd_size)
			*dsp_addr32++ = *buf_ptr++;
	}

	/* Set the mutex bits */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_M);
	ctrl_word |=  ADSP_RTOS_WRITE_CTRL_WORD_MUTEX_NAVAIL_V;

	/* Set the command bits to write done */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_CMD_M);
	ctrl_word |= ADSP_RTOS_WRITE_CTRL_WORD_CMD_WRITE_DONE_V;

	/* Set the queue address bits */
	ctrl_word &= ~(ADSP_RTOS_WRITE_CTRL_WORD_DSP_ADDR_M);
	ctrl_word |= dsp_q_addr;

	writel(ctrl_word, info->write_ctrl);

	/* Generate an interrupt to the DSP.  It does not respond with
	 * an interrupt, and we do not need to wait for it to
	 * acknowledge, because it will hold the mutex lock until it's
	 * ready to receive more commands again.
	 */
	writel(1, info->send_irq);

	module->num_commands++;

fail:
	spin_unlock_irqrestore(&adsp_cmd_lock, flags);
	return ret_status;
}