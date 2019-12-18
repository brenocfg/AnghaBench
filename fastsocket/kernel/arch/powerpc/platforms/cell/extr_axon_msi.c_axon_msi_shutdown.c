#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct of_device {int /*<<< orphan*/  dev; } ;
struct axon_msic {int /*<<< orphan*/  dcr_host; TYPE_2__* irq_host; } ;
struct TYPE_4__ {TYPE_1__* of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int MSIC_CTRL_ENABLE ; 
 int MSIC_CTRL_IRQ_ENABLE ; 
 int /*<<< orphan*/  MSIC_CTRL_REG ; 
 int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axon_msic* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msic_dcr_write (struct axon_msic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axon_msi_shutdown(struct of_device *device)
{
	struct axon_msic *msic = dev_get_drvdata(&device->dev);
	u32 tmp;

	pr_devel("axon_msi: disabling %s\n",
		  msic->irq_host->of_node->full_name);
	tmp  = dcr_read(msic->dcr_host, MSIC_CTRL_REG);
	tmp &= ~MSIC_CTRL_ENABLE & ~MSIC_CTRL_IRQ_ENABLE;
	msic_dcr_write(msic, MSIC_CTRL_REG, tmp);

	return 0;
}