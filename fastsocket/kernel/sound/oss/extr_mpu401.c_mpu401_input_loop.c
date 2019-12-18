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
struct mpu_config {int m_busy; scalar_t__ mode; int opened; int /*<<< orphan*/  devno; int /*<<< orphan*/  (* inputintr ) (int /*<<< orphan*/ ,unsigned char) ;int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ MODE_SYNTH ; 
 int OPEN_READ ; 
 scalar_t__ input_avail (struct mpu_config*) ; 
 int /*<<< orphan*/  mpu_input_scanner (struct mpu_config*,unsigned char) ; 
 unsigned char read_data (struct mpu_config*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void mpu401_input_loop(struct mpu_config *devc)
{
	unsigned long flags;
	int busy;
	int n;

	spin_lock_irqsave(&devc->lock,flags);
	busy = devc->m_busy;
	devc->m_busy = 1;
	spin_unlock_irqrestore(&devc->lock,flags);

	if (busy)		/* Already inside the scanner */
		return;

	n = 50;

	while (input_avail(devc) && n-- > 0)
	{
		unsigned char c = read_data(devc);

		if (devc->mode == MODE_SYNTH)
		{
			mpu_input_scanner(devc, c);
		}
		else if (devc->opened & OPEN_READ && devc->inputintr != NULL)
			devc->inputintr(devc->devno, c);
	}
	devc->m_busy = 0;
}