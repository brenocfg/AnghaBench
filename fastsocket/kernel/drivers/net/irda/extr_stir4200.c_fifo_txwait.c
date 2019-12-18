#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stir_cb {unsigned long* fifo_status; unsigned long speed; TYPE_1__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  FIFOCTL_CLR ; 
 unsigned long FIFOCTL_DIR ; 
 unsigned long FIFOCTL_EMPTY ; 
 int FIFO_REGS_SIZE ; 
 int /*<<< orphan*/  REG_FIFOCTL ; 
 int STIR_FIFO_SIZE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 
 int /*<<< orphan*/  netif_device_present (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int read_reg (struct stir_cb*,int /*<<< orphan*/ ,unsigned long*,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int write_reg (struct stir_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fifo_txwait(struct stir_cb *stir, int space)
{
	int err;
	unsigned long count, status;
	unsigned long prev_count = 0x1fff;

	/* Read FIFO status and count */
	for (;; prev_count = count) {
		err = read_reg(stir, REG_FIFOCTL, stir->fifo_status, 
				   FIFO_REGS_SIZE);
		if (unlikely(err != FIFO_REGS_SIZE)) {
			dev_warn(&stir->netdev->dev,
				 "FIFO register read error: %d\n", err);

			return err;
		}

		status = stir->fifo_status[0];
		count = (unsigned)(stir->fifo_status[2] & 0x1f) << 8 
			| stir->fifo_status[1];

		pr_debug("fifo status 0x%lx count %lu\n", status, count);

		/* is fifo receiving already, or empty */
		if (!(status & FIFOCTL_DIR)
		    || (status & FIFOCTL_EMPTY))
			return 0;

		if (signal_pending(current))
			return -EINTR;

		/* shutting down? */
		if (!netif_running(stir->netdev)
		    || !netif_device_present(stir->netdev))
			return -ESHUTDOWN;

		/* only waiting for some space */
		if (space >= 0 && STIR_FIFO_SIZE - 4 > space + count)
			return 0;

		/* queue confused */
		if (prev_count < count)
			break;

		/* estimate transfer time for remaining chars */
		msleep((count * 8000) / stir->speed);
	}
			
	err = write_reg(stir, REG_FIFOCTL, FIFOCTL_CLR);
	if (err) 
		return err;
	err = write_reg(stir, REG_FIFOCTL, 0);
	if (err)
		return err;

	return 0;
}