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
struct orc_scb {int dummy; } ;
struct orc_host {int /*<<< orphan*/  allocation_lock; } ;

/* Variables and functions */
 struct orc_scb* __orc_alloc_scb (struct orc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct orc_scb *orc_alloc_scb(struct orc_host * host)
{
	struct orc_scb *scb;
	unsigned long flags;

	spin_lock_irqsave(&host->allocation_lock, flags);
	scb = __orc_alloc_scb(host);
	spin_unlock_irqrestore(&host->allocation_lock, flags);
	return scb;
}