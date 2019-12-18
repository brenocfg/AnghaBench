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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qib_pportdata {int /*<<< orphan*/  port; scalar_t__ hw_pidx; struct qib_devdata* dd; } ;
struct qib_devdata {scalar_t__ twsi_eeprom_dev; int /*<<< orphan*/  eep_lock; int /*<<< orphan*/  (* f_gpio_mod ) (struct qib_devdata*,int,int,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 scalar_t__ QIB_TWSI_NO_DEV ; 
 int /*<<< orphan*/  QSFP_DEV ; 
 int QSFP_GPIO_LP_MODE ; 
 int QSFP_GPIO_MOD_RST_N ; 
 int QSFP_GPIO_MOD_SEL_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int QSFP_PAGESIZE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_porterr (struct qib_devdata*,int /*<<< orphan*/ ,char*) ; 
 int qib_twsi_blk_wr (struct qib_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int qib_twsi_reset (struct qib_devdata*) ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct qib_devdata*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qib_qsfp_write(struct qib_pportdata *ppd, int addr, void *bp,
			  int len)
{
	struct qib_devdata *dd = ppd->dd;
	u32 out, mask;
	int ret, cnt;
	u8 *buff = bp;

	ret = mutex_lock_interruptible(&dd->eep_lock);
	if (ret)
		goto no_unlock;

	if (dd->twsi_eeprom_dev == QIB_TWSI_NO_DEV) {
		ret = -ENXIO;
		goto bail;
	}

	/*
	 * We presume, if we are called at all, that this board has
	 * QSFP. This is on the same i2c chain as the legacy parts,
	 * but only responds if the module is selected via GPIO pins.
	 * Further, there are very long setup and hold requirements
	 * on MODSEL.
	 */
	mask = QSFP_GPIO_MOD_SEL_N | QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	out = QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	if (ppd->hw_pidx) {
		mask <<= QSFP_GPIO_PORT2_SHIFT;
		out <<= QSFP_GPIO_PORT2_SHIFT;
	}
	dd->f_gpio_mod(dd, out, mask, mask);

	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL,
	 * and there is no way to tell if it is ready, so we must wait.
	 */
	msleep(2);

	/* Make sure TWSI bus is in sane state. */
	ret = qib_twsi_reset(dd);
	if (ret) {
		qib_dev_porterr(dd, ppd->port,
				"QSFP interface Reset for write failed\n");
		ret = -EIO;
		goto deselect;
	}

	/* All QSFP modules are at A0 */

	cnt = 0;
	while (cnt < len) {
		unsigned in_page;
		int wlen = len - cnt;
		in_page = addr % QSFP_PAGESIZE;
		if ((in_page + wlen) > QSFP_PAGESIZE)
			wlen = QSFP_PAGESIZE - in_page;
		ret = qib_twsi_blk_wr(dd, QSFP_DEV, addr, buff + cnt, wlen);
		if (ret) {
			/* qib_twsi_blk_wr() 1 for error, else 0 */
			ret = -EIO;
			goto deselect;
		}
		addr += wlen;
		cnt += wlen;
	}
	ret = cnt;

deselect:
	/*
	 * Module could take up to 10 uSec after transfer before
	 * ready to respond to MOD_SEL negation, and there is no way
	 * to tell if it is ready, so we must wait.
	 */
	udelay(10);
	/* set QSFP MODSEL, RST, LP high */
	dd->f_gpio_mod(dd, mask, mask, mask);
	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL
	 * going away, and there is no way to tell if it is ready.
	 * so we must wait.
	 */
	msleep(2);

bail:
	mutex_unlock(&dd->eep_lock);

no_unlock:
	return ret;
}