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
 int /*<<< orphan*/  do_pf_request (int /*<<< orphan*/ ) ; 
 scalar_t__ pf_busy ; 
 int /*<<< orphan*/  pf_end_request (int) ; 
 int /*<<< orphan*/  pf_queue ; 
 int /*<<< orphan*/  pf_spin_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void next_request(int err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pf_spin_lock, saved_flags);
	pf_end_request(err);
	pf_busy = 0;
	do_pf_request(pf_queue);
	spin_unlock_irqrestore(&pf_spin_lock, saved_flags);
}