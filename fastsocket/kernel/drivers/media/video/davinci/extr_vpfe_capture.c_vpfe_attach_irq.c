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
struct vpfe_device {int /*<<< orphan*/  ccdc_irq1; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;
struct TYPE_3__ {int (* get_frame_format ) () ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int CCDC_FRMFMT_PROGRESSIVE ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 TYPE_2__* ccdc_dev ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vpfe_device*) ; 
 int stub1 () ; 
 int /*<<< orphan*/  vdint1_isr ; 

__attribute__((used)) static int vpfe_attach_irq(struct vpfe_device *vpfe_dev)
{
	enum ccdc_frmfmt frame_format;

	frame_format = ccdc_dev->hw_ops.get_frame_format();
	if (frame_format == CCDC_FRMFMT_PROGRESSIVE) {
		return request_irq(vpfe_dev->ccdc_irq1, vdint1_isr,
				    IRQF_DISABLED, "vpfe_capture1",
				    vpfe_dev);
	}
	return 0;
}