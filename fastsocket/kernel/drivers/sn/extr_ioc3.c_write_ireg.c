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
typedef  int /*<<< orphan*/  uint32_t ;
struct ioc3_driver_data {int /*<<< orphan*/  ir_lock; TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  sio_iec; int /*<<< orphan*/  sio_ies; } ;

/* Variables and functions */
#define  IOC3_W_IEC 129 
#define  IOC3_W_IES 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_ireg(struct ioc3_driver_data *idd, uint32_t val, int which)
{
	unsigned long flags;

	spin_lock_irqsave(&idd->ir_lock, flags);
	switch (which) {
	case IOC3_W_IES:
		writel(val, &idd->vma->sio_ies);
		break;
	case IOC3_W_IEC:
		writel(val, &idd->vma->sio_iec);
		break;
	}
	spin_unlock_irqrestore(&idd->ir_lock, flags);
}