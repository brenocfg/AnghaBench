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
typedef  int u16 ;
struct usb_hcd {int dummy; } ;
struct tmio_hcd {int /*<<< orphan*/  lock; scalar_t__ ccr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCR_PM ; 
 int CCR_PM_CKRNEN ; 
 int CCR_PM_GKEN ; 
 int CCR_PM_PMEE ; 
 int CCR_PM_PMES ; 
 struct tmio_hcd* hcd_to_tmio (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void tmio_write_pm(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct tmio_hcd *tmio = hcd_to_tmio(hcd);
	u16 pm;
	unsigned long flags;

	spin_lock_irqsave(&tmio->lock, flags);

	pm = CCR_PM_GKEN | CCR_PM_CKRNEN |
	     CCR_PM_PMEE | CCR_PM_PMES;

	tmio_iowrite16(pm, tmio->ccr + CCR_PM);
	spin_unlock_irqrestore(&tmio->lock, flags);
}