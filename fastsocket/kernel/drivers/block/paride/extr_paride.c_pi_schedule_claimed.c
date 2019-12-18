#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void (* claim_cont ) () ;int claimed; scalar_t__ pardev; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 scalar_t__ parport_claim (scalar_t__) ; 
 int /*<<< orphan*/  pi_spinlock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pi_schedule_claimed(PIA * pi, void (*cont) (void))
{
	unsigned long flags;

	spin_lock_irqsave(&pi_spinlock, flags);
	if (pi->pardev && parport_claim(pi->pardev)) {
		pi->claim_cont = cont;
		spin_unlock_irqrestore(&pi_spinlock, flags);
		return 0;
	}
	pi->claimed = 1;
	spin_unlock_irqrestore(&pi_spinlock, flags);
	return 1;
}