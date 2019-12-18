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
typedef  int u32 ;
struct whc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; scalar_t__ base; scalar_t__ gen_cmd_buf_dma; int /*<<< orphan*/  gen_cmd_buf; TYPE_1__* umc; int /*<<< orphan*/  cmd_wq; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WHC_GENCMD_TIMEOUT_MS ; 
 scalar_t__ WUSBGENADDR ; 
 scalar_t__ WUSBGENCMDPARAMS ; 
 scalar_t__ WUSBGENCMDSTS ; 
 int WUSBGENCMDSTS_ACTIVE ; 
 int WUSBGENCMDSTS_IOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  le_writeq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int whc_do_gencmd(struct whc *whc, u32 cmd, u32 params, void *addr, size_t len)
{
	unsigned long flags;
	dma_addr_t dma_addr;
	int t;
	int ret = 0;

	mutex_lock(&whc->mutex);

	/* Wait for previous command to complete. */
	t = wait_event_timeout(whc->cmd_wq,
			       (le_readl(whc->base + WUSBGENCMDSTS) & WUSBGENCMDSTS_ACTIVE) == 0,
			       WHC_GENCMD_TIMEOUT_MS);
	if (t == 0) {
		dev_err(&whc->umc->dev, "generic command timeout (%04x/%04x)\n",
			le_readl(whc->base + WUSBGENCMDSTS),
			le_readl(whc->base + WUSBGENCMDPARAMS));
		ret = -ETIMEDOUT;
		goto out;
	}

	if (addr) {
		memcpy(whc->gen_cmd_buf, addr, len);
		dma_addr = whc->gen_cmd_buf_dma;
	} else
		dma_addr = 0;

	/* Poke registers to start cmd. */
	spin_lock_irqsave(&whc->lock, flags);

	le_writel(params, whc->base + WUSBGENCMDPARAMS);
	le_writeq(dma_addr, whc->base + WUSBGENADDR);

	le_writel(WUSBGENCMDSTS_ACTIVE | WUSBGENCMDSTS_IOC | cmd,
		  whc->base + WUSBGENCMDSTS);

	spin_unlock_irqrestore(&whc->lock, flags);
out:
	mutex_unlock(&whc->mutex);

	return ret;
}