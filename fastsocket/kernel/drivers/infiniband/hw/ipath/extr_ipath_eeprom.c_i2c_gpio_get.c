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
typedef  int u64 ;
struct ipath_devdata {int ipath_gpio_scl; int ipath_gpio_sda; int ipath_extctrl; int /*<<< orphan*/  ipath_gpio_lock; TYPE_1__* ipath_kregs; } ;
typedef  enum i2c_type { ____Placeholder_i2c_type } i2c_type ;
typedef  enum i2c_state { ____Placeholder_i2c_state } i2c_state ;
struct TYPE_2__ {int /*<<< orphan*/  kr_extstatus; int /*<<< orphan*/  kr_extctrl; } ;

/* Variables and functions */
 int i2c_line_high ; 
 int i2c_line_low ; 
 int i2c_line_scl ; 
 int ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int i2c_gpio_get(struct ipath_devdata *dd,
			enum i2c_type line,
			enum i2c_state *curr_statep)
{
	u64 read_val, mask;
	int ret;
	unsigned long flags = 0;

	/* check args */
	if (curr_statep == NULL) {
		ret = 1;
		goto bail;
	}

	/* config line to be an input */
	if (line == i2c_line_scl)
		mask = dd->ipath_gpio_scl;
	else
		mask = dd->ipath_gpio_sda;

	spin_lock_irqsave(&dd->ipath_gpio_lock, flags);
	dd->ipath_extctrl &= ~mask;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_extctrl, dd->ipath_extctrl);
	/*
	 * Below is very unlikely to reflect true input state if Output
	 * Enable actually changed.
	 */
	read_val = ipath_read_kreg64(dd, dd->ipath_kregs->kr_extstatus);
	spin_unlock_irqrestore(&dd->ipath_gpio_lock, flags);

	if (read_val & mask)
		*curr_statep = i2c_line_high;
	else
		*curr_statep = i2c_line_low;

	ret = 0;

bail:
	return ret;
}