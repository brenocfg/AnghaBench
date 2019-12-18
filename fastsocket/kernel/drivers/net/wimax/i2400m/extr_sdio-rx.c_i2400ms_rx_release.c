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
struct device {int dummy; } ;
struct sdio_func {struct device dev; } ;
struct i2400m {int /*<<< orphan*/  rx_lock; } ;
struct i2400ms {int /*<<< orphan*/  bm_wfa_wq; int /*<<< orphan*/  bm_ack_size; struct i2400m i2400m; struct sdio_func* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  I2400MS_INTR_ENABLE_ADDR ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400ms*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400ms*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void i2400ms_rx_release(struct i2400ms *i2400ms)
{
	int result;
	struct sdio_func *func = i2400ms->func;
	struct device *dev = &func->dev;
	struct i2400m *i2400m = &i2400ms->i2400m;

	d_fnstart(5, dev, "(i2400ms %p)\n", i2400ms);
	spin_lock(&i2400m->rx_lock);
	i2400ms->bm_ack_size = -EINTR;
	spin_unlock(&i2400m->rx_lock);
	wake_up_all(&i2400ms->bm_wfa_wq);
	sdio_claim_host(func);
	sdio_writeb(func, 0, I2400MS_INTR_ENABLE_ADDR, &result);
	sdio_release_irq(func);
	sdio_release_host(func);
	d_fnend(5, dev, "(i2400ms %p) = %d\n", i2400ms, result);
}