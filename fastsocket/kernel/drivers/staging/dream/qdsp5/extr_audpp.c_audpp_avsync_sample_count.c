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
typedef  unsigned int uint16_t ;
struct TYPE_2__ {unsigned int* avsync; } ;

/* Variables and functions */
 int AUDPP_AVSYNC_INFO_SIZE ; 
 scalar_t__ BAD_ID (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ the_audpp_state ; 

unsigned audpp_avsync_sample_count(int id)
{
	uint16_t *avsync = the_audpp_state.avsync;
	unsigned val;
	unsigned long flags;
	unsigned mask;

	if (BAD_ID(id))
		return 0;

	mask = 1 << id;
	id = id * AUDPP_AVSYNC_INFO_SIZE + 2;
	local_irq_save(flags);
	if (avsync[0] & mask)
		val = (avsync[id] << 16) | avsync[id + 1];
	else
		val = 0;
	local_irq_restore(flags);

	return val;
}