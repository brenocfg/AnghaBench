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
struct TYPE_2__ {struct m48t59_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t59_private {int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  M48T59_INTR ; 
 int M48T59_INTR_AFE ; 
 int /*<<< orphan*/  M48T59_WRITE (int,int /*<<< orphan*/ ) ; 
#define  RTC_AIE_OFF 129 
#define  RTC_AIE_ON 128 
 struct m48t59_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int m48t59_rtc_ioctl(struct device *dev, unsigned int cmd,
			unsigned long arg)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = pdev->dev.platform_data;
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&m48t59->lock, flags);
	switch (cmd) {
	case RTC_AIE_OFF:	/* alarm interrupt off */
		M48T59_WRITE(0x00, M48T59_INTR);
		break;
	case RTC_AIE_ON:	/* alarm interrupt on */
		M48T59_WRITE(M48T59_INTR_AFE, M48T59_INTR);
		break;
	default:
		ret = -ENOIOCTLCMD;
		break;
	}
	spin_unlock_irqrestore(&m48t59->lock, flags);

	return ret;
}