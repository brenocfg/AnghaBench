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
 unsigned int ERR_FLAG_BOOT ; 
#define  ERR_TYPE_KERNEL_PANIC 129 
 unsigned int ERR_TYPE_MASK ; 
#define  ERR_TYPE_RTAS_LOG 128 
 int LOG_NUMBER ; 
 int LOG_NUMBER_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  error_log_cnt ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int log_rtas_len (char*) ; 
 scalar_t__ logging_enabled ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvram_write_error_log (char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  printk_log_rtas (char*,int) ; 
 int rtas_error_log_buffer_max ; 
 int /*<<< orphan*/ * rtas_log_buf ; 
 int rtas_log_size ; 
 int rtas_log_start ; 
 int /*<<< orphan*/  rtas_log_wait ; 
 int /*<<< orphan*/  rtasd_log_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void pSeries_log_error(char *buf, unsigned int err_type, int fatal)
{
	unsigned long offset;
	unsigned long s;
	int len = 0;

	pr_debug("rtasd: logging event\n");
	if (buf == NULL)
		return;

	spin_lock_irqsave(&rtasd_log_lock, s);

	/* get length and increase count */
	switch (err_type & ERR_TYPE_MASK) {
	case ERR_TYPE_RTAS_LOG:
		len = log_rtas_len(buf);
		if (!(err_type & ERR_FLAG_BOOT))
			error_log_cnt++;
		break;
	case ERR_TYPE_KERNEL_PANIC:
	default:
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		return;
	}

	/* Write error to NVRAM */
	if (logging_enabled && !(err_type & ERR_FLAG_BOOT))
		nvram_write_error_log(buf, len, err_type, error_log_cnt);

	/*
	 * rtas errors can occur during boot, and we do want to capture
	 * those somewhere, even if nvram isn't ready (why not?), and even
	 * if rtasd isn't ready. Put them into the boot log, at least.
	 */
	if ((err_type & ERR_TYPE_MASK) == ERR_TYPE_RTAS_LOG)
		printk_log_rtas(buf, len);

	/* Check to see if we need to or have stopped logging */
	if (fatal || !logging_enabled) {
		logging_enabled = 0;
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		return;
	}

	/* call type specific method for error */
	switch (err_type & ERR_TYPE_MASK) {
	case ERR_TYPE_RTAS_LOG:
		offset = rtas_error_log_buffer_max *
			((rtas_log_start+rtas_log_size) & LOG_NUMBER_MASK);

		/* First copy over sequence number */
		memcpy(&rtas_log_buf[offset], (void *) &error_log_cnt, sizeof(int));

		/* Second copy over error log data */
		offset += sizeof(int);
		memcpy(&rtas_log_buf[offset], buf, len);

		if (rtas_log_size < LOG_NUMBER)
			rtas_log_size += 1;
		else
			rtas_log_start += 1;

		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		wake_up_interruptible(&rtas_log_wait);
		break;
	case ERR_TYPE_KERNEL_PANIC:
	default:
		WARN_ON_ONCE(!irqs_disabled()); /* @@@ DEBUG @@@ */
		spin_unlock_irqrestore(&rtasd_log_lock, s);
		return;
	}

}