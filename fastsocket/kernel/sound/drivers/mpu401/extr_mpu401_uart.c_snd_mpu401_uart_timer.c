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
struct TYPE_2__ {scalar_t__ expires; } ;
struct snd_mpu401 {scalar_t__ rmidi; int /*<<< orphan*/  timer_lock; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _snd_mpu401_uart_interrupt (struct snd_mpu401*) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_mpu401_uart_timer(unsigned long data)
{
	struct snd_mpu401 *mpu = (struct snd_mpu401 *)data;
	unsigned long flags;

	spin_lock_irqsave(&mpu->timer_lock, flags);
	/*mpu->mode |= MPU401_MODE_TIMER;*/
	mpu->timer.expires = 1 + jiffies;
	add_timer(&mpu->timer);
	spin_unlock_irqrestore(&mpu->timer_lock, flags);
	if (mpu->rmidi)
		_snd_mpu401_uart_interrupt(mpu);
}