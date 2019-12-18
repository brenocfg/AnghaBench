#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int port_num; int irq_occurred; int /*<<< orphan*/  lock; int /*<<< orphan*/  init_error; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ BIT4 ; 
 scalar_t__ BIT6 ; 
 int /*<<< orphan*/  DiagStatus_IrqFailure ; 
 unsigned char IER2 ; 
 scalar_t__ TCONR ; 
 scalar_t__ TEPR ; 
 unsigned char TIMER0 ; 
 unsigned char TIMER2 ; 
 scalar_t__ TMCS ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  reset_port (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,unsigned char,int) ; 
 int /*<<< orphan*/  write_reg16 (TYPE_1__*,unsigned char,int) ; 

__attribute__((used)) static bool irq_test(SLMP_INFO *info)
{
	unsigned long timeout;
	unsigned long flags;

	unsigned char timer = (info->port_num & 1) ? TIMER2 : TIMER0;

	spin_lock_irqsave(&info->lock,flags);
	reset_port(info);

	/* assume failure */
	info->init_error = DiagStatus_IrqFailure;
	info->irq_occurred = false;

	/* setup timer0 on SCA0 to interrupt */

	/* IER2<7..4> = timer<3..0> interrupt enables (1=enabled) */
	write_reg(info, IER2, (unsigned char)((info->port_num & 1) ? BIT6 : BIT4));

	write_reg(info, (unsigned char)(timer + TEPR), 0);	/* timer expand prescale */
	write_reg16(info, (unsigned char)(timer + TCONR), 1);	/* timer constant */


	/* TMCS, Timer Control/Status Register
	 *
	 * 07      CMF, Compare match flag (read only) 1=match
	 * 06      ECMI, CMF Interrupt Enable: 1=enabled
	 * 05      Reserved, must be 0
	 * 04      TME, Timer Enable
	 * 03..00  Reserved, must be 0
	 *
	 * 0101 0000
	 */
	write_reg(info, (unsigned char)(timer + TMCS), 0x50);

	spin_unlock_irqrestore(&info->lock,flags);

	timeout=100;
	while( timeout-- && !info->irq_occurred ) {
		msleep_interruptible(10);
	}

	spin_lock_irqsave(&info->lock,flags);
	reset_port(info);
	spin_unlock_irqrestore(&info->lock,flags);

	return info->irq_occurred;
}