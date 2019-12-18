#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rwlock_t ;
struct TYPE_2__ {scalar_t__ ibf; int /*<<< orphan*/  status_io; int /*<<< orphan*/  ibf_lock; } ;

/* Variables and functions */
 int HP_SDC_STATUS_IBF ; 
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sdc_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void hp_sdc_spin_ibf(void)
{
	unsigned long flags;
	rwlock_t *lock;

	lock = &hp_sdc.ibf_lock;

	read_lock_irqsave(lock, flags);
	if (!hp_sdc.ibf) {
		read_unlock_irqrestore(lock, flags);
		return;
	}
	read_unlock(lock);
	write_lock(lock);
	while (sdc_readb(hp_sdc.status_io) & HP_SDC_STATUS_IBF)
		{ }
	hp_sdc.ibf = 0;
	write_unlock_irqrestore(lock, flags);
}