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
struct wm831x {int irq; int* irq_masks; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  irq_wq; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int ESRCH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ WM831X_INTERRUPT_STATUS_1_MASK ; 
 scalar_t__ WM831X_SYSTEM_INTERRUPTS_MASK ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,char*,struct wm831x*) ; 
 int /*<<< orphan*/  wm831x_cpu_irq ; 
 int /*<<< orphan*/  wm831x_irq_worker ; 
 int /*<<< orphan*/  wm831x_reg_write (struct wm831x*,scalar_t__,int) ; 

int wm831x_irq_init(struct wm831x *wm831x, int irq)
{
	int i, ret;

	mutex_init(&wm831x->irq_lock);

	if (!irq) {
		dev_warn(wm831x->dev,
			 "No interrupt specified - functionality limited\n");
		return 0;
	}


	wm831x->irq_wq = create_singlethread_workqueue("wm831x-irq");
	if (!wm831x->irq_wq) {
		dev_err(wm831x->dev, "Failed to allocate IRQ worker\n");
		return -ESRCH;
	}

	wm831x->irq = irq;
	INIT_WORK(&wm831x->irq_work, wm831x_irq_worker);

	/* Mask the individual interrupt sources */
	for (i = 0; i < ARRAY_SIZE(wm831x->irq_masks); i++) {
		wm831x->irq_masks[i] = 0xffff;
		wm831x_reg_write(wm831x, WM831X_INTERRUPT_STATUS_1_MASK + i,
				 0xffff);
	}

	/* Enable top level interrupts, we mask at secondary level */
	wm831x_reg_write(wm831x, WM831X_SYSTEM_INTERRUPTS_MASK, 0);

	/* We're good to go.  We set IRQF_SHARED since there's a
	 * chance the driver will interoperate with another driver but
	 * the need to disable the IRQ while handing via I2C/SPI means
	 * that this may break and performance will be impacted.  If
	 * this does happen it's a hardware design issue and the only
	 * other alternative would be polling.
	 */
	ret = request_irq(irq, wm831x_cpu_irq, IRQF_TRIGGER_LOW | IRQF_SHARED,
			  "wm831x", wm831x);
	if (ret != 0) {
		dev_err(wm831x->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		return ret;
	}

	return 0;
}