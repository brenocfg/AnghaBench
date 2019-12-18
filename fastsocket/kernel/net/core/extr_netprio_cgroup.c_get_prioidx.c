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
typedef  int u32 ;

/* Variables and functions */
 int ENOSPC ; 
 int PRIOIDX_SZ ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_prioidx ; 
 int /*<<< orphan*/  prioidx_map ; 
 int /*<<< orphan*/  prioidx_map_lock ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_prioidx(u32 *prio)
{
	unsigned long flags;
	u32 prioidx;

	spin_lock_irqsave(&prioidx_map_lock, flags);
	prioidx = find_first_zero_bit(prioidx_map, sizeof(unsigned long) * PRIOIDX_SZ);

	if (prioidx == sizeof(unsigned long) * PRIOIDX_SZ) {
		spin_unlock_irqrestore(&prioidx_map_lock, flags);
		return -ENOSPC;
	}

	set_bit(prioidx, prioidx_map);
	if (atomic_read(&max_prioidx) < prioidx)
		atomic_set(&max_prioidx, prioidx);
	spin_unlock_irqrestore(&prioidx_map_lock, flags);

	*prio = prioidx;
	return 0;
}