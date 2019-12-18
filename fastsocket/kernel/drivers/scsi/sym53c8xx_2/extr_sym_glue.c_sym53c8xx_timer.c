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
struct TYPE_4__ {TYPE_1__* host; } ;
struct sym_hcb {TYPE_2__ s; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sym_timer (struct sym_hcb*) ; 

__attribute__((used)) static void sym53c8xx_timer(unsigned long npref)
{
	struct sym_hcb *np = (struct sym_hcb *)npref;
	unsigned long flags;

	spin_lock_irqsave(np->s.host->host_lock, flags);
	sym_timer(np);
	spin_unlock_irqrestore(np->s.host->host_lock, flags);
}