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
struct TYPE_2__ {int cpu_signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGLOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MP_TLB_FLUSH ; 
 int /*<<< orphan*/  cpu_handle ; 
 int /*<<< orphan*/  cpu_number () ; 
 TYPE_1__* current_cpu_datap () ; 
 scalar_t__ i_bit (int /*<<< orphan*/ ,int volatile*) ; 
 int /*<<< orphan*/  i_bit_clear (int /*<<< orphan*/ ,int volatile*) ; 
 scalar_t__ pmap_tlb_flush_timeout ; 
 int /*<<< orphan*/  pmap_update_interrupt () ; 

void
handle_pending_TLB_flushes(void)
{
	volatile int	*my_word = &current_cpu_datap()->cpu_signals;

	if (i_bit(MP_TLB_FLUSH, my_word)  && (pmap_tlb_flush_timeout == FALSE)) {
		DBGLOG(cpu_handle, cpu_number(), MP_TLB_FLUSH);
		i_bit_clear(MP_TLB_FLUSH, my_word);
		pmap_update_interrupt();
	}
}