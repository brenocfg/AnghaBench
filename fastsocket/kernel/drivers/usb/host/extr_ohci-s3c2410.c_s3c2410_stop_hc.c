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
struct s3c2410_hcd_info {int /*<<< orphan*/  (* enable_oc ) (struct s3c2410_hcd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * hcd; int /*<<< orphan*/ * report_oc; } ;
struct TYPE_2__ {struct s3c2410_hcd_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub1 (struct s3c2410_hcd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clk ; 

__attribute__((used)) static void s3c2410_stop_hc(struct platform_device *dev)
{
	struct s3c2410_hcd_info *info = dev->dev.platform_data;

	dev_dbg(&dev->dev, "s3c2410_stop_hc:\n");

	if (info != NULL) {
		info->report_oc = NULL;
		info->hcd	= NULL;

		if (info->enable_oc != NULL) {
			(info->enable_oc)(info, 0);
		}
	}

	clk_disable(clk);
	clk_disable(usb_clk);
}