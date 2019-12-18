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
typedef  unsigned long u64 ;
struct ipath_devdata {unsigned long ipath_gpio_out; unsigned long ipath_gpio_scl; unsigned long ipath_gpio_scl_num; unsigned long ipath_gpio_sda; unsigned long ipath_gpio_sda_num; unsigned long ipath_extctrl; int /*<<< orphan*/  ipath_gpio_lock; TYPE_1__* ipath_kregs; } ;
typedef  enum i2c_type { ____Placeholder_i2c_type } i2c_type ;
typedef  enum i2c_state { ____Placeholder_i2c_state } i2c_state ;
struct TYPE_2__ {int /*<<< orphan*/  kr_gpio_out; int /*<<< orphan*/  kr_extctrl; } ;

/* Variables and functions */
 int i2c_line_high ; 
 int i2c_line_scl ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int i2c_gpio_set(struct ipath_devdata *dd,
			enum i2c_type line,
			enum i2c_state new_line_state)
{
	u64 out_mask, dir_mask, *gpioval;
	unsigned long flags = 0;

	gpioval = &dd->ipath_gpio_out;

	if (line == i2c_line_scl) {
		dir_mask = dd->ipath_gpio_scl;
		out_mask = (1UL << dd->ipath_gpio_scl_num);
	} else {
		dir_mask = dd->ipath_gpio_sda;
		out_mask = (1UL << dd->ipath_gpio_sda_num);
	}

	spin_lock_irqsave(&dd->ipath_gpio_lock, flags);
	if (new_line_state == i2c_line_high) {
		/* tri-state the output rather than force high */
		dd->ipath_extctrl &= ~dir_mask;
	} else {
		/* config line to be an output */
		dd->ipath_extctrl |= dir_mask;
	}
	ipath_write_kreg(dd, dd->ipath_kregs->kr_extctrl, dd->ipath_extctrl);

	/* set output as well (no real verify) */
	if (new_line_state == i2c_line_high)
		*gpioval |= out_mask;
	else
		*gpioval &= ~out_mask;

	ipath_write_kreg(dd, dd->ipath_kregs->kr_gpio_out, *gpioval);
	spin_unlock_irqrestore(&dd->ipath_gpio_lock, flags);

	return 0;
}