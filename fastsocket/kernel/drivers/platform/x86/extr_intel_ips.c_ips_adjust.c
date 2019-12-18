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
struct ips_driver {TYPE_1__* dev; scalar_t__ gpu_turbo_enabled; scalar_t__ cpu_turbo_enabled; int /*<<< orphan*/  turbo_status_lock; scalar_t__ poll_turbo_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_ADJUST_PERIOD ; 
 int /*<<< orphan*/  cpu_exceeded (struct ips_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int ips_cpu_busy (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_cpu_lower (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_cpu_raise (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_disable_cpu_turbo (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_disable_gpu_turbo (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_enable_cpu_turbo (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_enable_gpu_turbo (struct ips_driver*) ; 
 int ips_gpu_busy (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_gpu_lower (struct ips_driver*) ; 
 int /*<<< orphan*/  ips_gpu_raise (struct ips_driver*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mch_exceeded (struct ips_driver*) ; 
 scalar_t__ mcp_exceeded (struct ips_driver*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_turbo_limits (struct ips_driver*) ; 

__attribute__((used)) static int ips_adjust(void *data)
{
	struct ips_driver *ips = data;
	unsigned long flags;

	dev_dbg(&ips->dev->dev, "starting ips-adjust thread\n");

	/*
	 * Adjust CPU and GPU clamps every 5s if needed.  Doing it more
	 * often isn't recommended due to ME interaction.
	 */
	do {
		bool cpu_busy = ips_cpu_busy(ips);
		bool gpu_busy = ips_gpu_busy(ips);

		spin_lock_irqsave(&ips->turbo_status_lock, flags);
		if (ips->poll_turbo_status)
			update_turbo_limits(ips);
		spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

		/* Update turbo status if necessary */
		if (ips->cpu_turbo_enabled)
			ips_enable_cpu_turbo(ips);
		else
			ips_disable_cpu_turbo(ips);

		if (ips->gpu_turbo_enabled)
			ips_enable_gpu_turbo(ips);
		else
			ips_disable_gpu_turbo(ips);

		/* We're outside our comfort zone, crank them down */
		if (mcp_exceeded(ips)) {
			ips_cpu_lower(ips);
			ips_gpu_lower(ips);
			goto sleep;
		}

		if (!cpu_exceeded(ips, 0) && cpu_busy)
			ips_cpu_raise(ips);
		else
			ips_cpu_lower(ips);

		if (!mch_exceeded(ips) && gpu_busy)
			ips_gpu_raise(ips);
		else
			ips_gpu_lower(ips);

sleep:
		schedule_timeout_interruptible(msecs_to_jiffies(IPS_ADJUST_PERIOD));
	} while (!kthread_should_stop());

	dev_dbg(&ips->dev->dev, "ips-adjust thread stopped\n");

	return 0;
}