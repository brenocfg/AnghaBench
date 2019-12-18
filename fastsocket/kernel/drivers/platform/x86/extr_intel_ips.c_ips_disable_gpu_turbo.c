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
struct ips_driver {int __gpu_turbo_on; TYPE_1__* dev; int /*<<< orphan*/  (* gpu_turbo_disable ) () ;} ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void ips_disable_gpu_turbo(struct ips_driver *ips)
{
	/* Avoid calling i915 if turbo is already disabled */
	if (!ips->__gpu_turbo_on)
		return;

	if (!ips->gpu_turbo_disable())
		dev_err(&ips->dev->dev, "failed to disable graphis turbo\n");
	else
		ips->__gpu_turbo_on = false;
}