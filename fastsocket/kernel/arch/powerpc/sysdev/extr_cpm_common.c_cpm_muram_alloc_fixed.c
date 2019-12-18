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
struct TYPE_3__ {int alignment; } ;

/* Variables and functions */
 TYPE_1__ cpm_muram_info ; 
 int /*<<< orphan*/  cpm_muram_lock ; 
 unsigned long rh_alloc_fixed (TYPE_1__*,unsigned long,unsigned long,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long cpm_muram_alloc_fixed(unsigned long offset, unsigned long size)
{
	unsigned long start;
	unsigned long flags;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	cpm_muram_info.alignment = 1;
	start = rh_alloc_fixed(&cpm_muram_info, offset, size, "commproc");
	spin_unlock_irqrestore(&cpm_muram_lock, flags);

	return start;
}