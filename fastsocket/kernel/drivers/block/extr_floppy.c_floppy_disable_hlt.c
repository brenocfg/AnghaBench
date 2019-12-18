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

/* Variables and functions */
 int /*<<< orphan*/  disable_hlt () ; 
 int /*<<< orphan*/  floppy_hlt_lock ; 
 int hlt_disabled ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void floppy_disable_hlt(void)
{
	unsigned long flags;

	spin_lock_irqsave(&floppy_hlt_lock, flags);
	if (!hlt_disabled) {
		hlt_disabled = 1;
#ifdef HAVE_DISABLE_HLT
		disable_hlt();
#endif
	}
	spin_unlock_irqrestore(&floppy_hlt_lock, flags);
}