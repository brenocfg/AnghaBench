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
struct wm8350 {int /*<<< orphan*/  irq_mutex; TYPE_1__* irq; } ;
struct TYPE_2__ {void (* handler ) (struct wm8350*,int,void*) ;void* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int WM8350_NUM_IRQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int wm8350_register_irq(struct wm8350 *wm8350, int irq,
			void (*handler) (struct wm8350 *, int, void *),
			void *data)
{
	if (irq < 0 || irq > WM8350_NUM_IRQ || !handler)
		return -EINVAL;

	if (wm8350->irq[irq].handler)
		return -EBUSY;

	mutex_lock(&wm8350->irq_mutex);
	wm8350->irq[irq].handler = handler;
	wm8350->irq[irq].data = data;
	mutex_unlock(&wm8350->irq_mutex);

	return 0;
}