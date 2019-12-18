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
struct ub_dev {scalar_t__ openc; int /*<<< orphan*/  poison; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ub_cleanup (struct ub_dev*) ; 
 int /*<<< orphan*/  ub_lock ; 

__attribute__((used)) static void ub_put(struct ub_dev *sc)
{
	unsigned long flags;

	spin_lock_irqsave(&ub_lock, flags);
	--sc->openc;
	if (sc->openc == 0 && atomic_read(&sc->poison)) {
		spin_unlock_irqrestore(&ub_lock, flags);
		ub_cleanup(sc);
	} else {
		spin_unlock_irqrestore(&ub_lock, flags);
	}
}