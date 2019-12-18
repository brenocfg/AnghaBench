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
struct seq_file {int dummy; } ;
struct TYPE_2__ {struct m48t86_ops* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t86_ops {unsigned char (* readbyte ) (int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T86_REG_B ; 
 unsigned char M48T86_REG_B_DM ; 
 int /*<<< orphan*/  M48T86_REG_D ; 
 unsigned char M48T86_REG_D_VRT ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 unsigned char stub1 (int /*<<< orphan*/ ) ; 
 unsigned char stub2 (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int m48t86_rtc_proc(struct device *dev, struct seq_file *seq)
{
	unsigned char reg;
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t86_ops *ops = pdev->dev.platform_data;

	reg = ops->readbyte(M48T86_REG_B);

	seq_printf(seq, "mode\t\t: %s\n",
		 (reg & M48T86_REG_B_DM) ? "binary" : "bcd");

	reg = ops->readbyte(M48T86_REG_D);

	seq_printf(seq, "battery\t\t: %s\n",
		 (reg & M48T86_REG_D_VRT) ? "ok" : "exhausted");

	return 0;
}