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
struct vpfe_device {int started; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_out_to_sdram ) (int) ;int /*<<< orphan*/  (* enable ) (int) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 TYPE_2__* ccdc_dev ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void vpfe_start_ccdc_capture(struct vpfe_device *vpfe_dev)
{
	ccdc_dev->hw_ops.enable(1);
	if (ccdc_dev->hw_ops.enable_out_to_sdram)
		ccdc_dev->hw_ops.enable_out_to_sdram(1);
	vpfe_dev->started = 1;
}