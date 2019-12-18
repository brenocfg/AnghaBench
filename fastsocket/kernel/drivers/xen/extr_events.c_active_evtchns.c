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
struct shared_info {unsigned long* evtchn_pending; unsigned long* evtchn_mask; } ;

/* Variables and functions */
 unsigned long* cpu_evtchn_mask (unsigned int) ; 

__attribute__((used)) static inline unsigned long active_evtchns(unsigned int cpu,
					   struct shared_info *sh,
					   unsigned int idx)
{
	return (sh->evtchn_pending[idx] &
		cpu_evtchn_mask(cpu)[idx] &
		~sh->evtchn_mask[idx]);
}