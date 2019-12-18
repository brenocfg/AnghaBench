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
typedef  int uint ;
typedef  size_t u32 ;
struct qib_devdata {int* eep_st_new_errs; int /*<<< orphan*/  eep_st_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void qib_inc_eeprom_err(struct qib_devdata *dd, u32 eidx, u32 incr)
{
	uint new_val;
	unsigned long flags;

	spin_lock_irqsave(&dd->eep_st_lock, flags);
	new_val = dd->eep_st_new_errs[eidx] + incr;
	if (new_val > 255)
		new_val = 255;
	dd->eep_st_new_errs[eidx] = new_val;
	spin_unlock_irqrestore(&dd->eep_st_lock, flags);
}