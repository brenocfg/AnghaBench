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
 int /*<<< orphan*/  cpm_muram_info ; 
 int /*<<< orphan*/  cpm_muram_lock ; 
 int rh_free (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpm_muram_free(unsigned long offset)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	ret = rh_free(&cpm_muram_info, offset);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);

	return ret;
}