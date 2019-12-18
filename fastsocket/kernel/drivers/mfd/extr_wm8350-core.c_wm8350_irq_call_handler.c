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
struct wm8350 {int /*<<< orphan*/  irq_mutex; int /*<<< orphan*/  dev; TYPE_1__* irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (struct wm8350*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wm8350*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_mask_irq (struct wm8350*,int) ; 

__attribute__((used)) static void wm8350_irq_call_handler(struct wm8350 *wm8350, int irq)
{
	mutex_lock(&wm8350->irq_mutex);

	if (wm8350->irq[irq].handler)
		wm8350->irq[irq].handler(wm8350, irq, wm8350->irq[irq].data);
	else {
		dev_err(wm8350->dev, "irq %d nobody cared. now masked.\n",
			irq);
		wm8350_mask_irq(wm8350, irq);
	}

	mutex_unlock(&wm8350->irq_mutex);
}