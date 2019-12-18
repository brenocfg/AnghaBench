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
typedef  int uint64_t ;
typedef  scalar_t__ mp_sync_t ;
typedef  int /*<<< orphan*/  mp_event_t ;
struct TYPE_2__ {int cpu_signals; int /*<<< orphan*/  cpu_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGLOG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_TLB_FLUSH ; 
 scalar_t__ SYNC ; 
 int TRACE_MP_TLB_FLUSH ; 
 TYPE_1__* cpu_datap (int) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  cpu_signal ; 
 int /*<<< orphan*/  i386_cpu_IPI (int) ; 
 scalar_t__ i_bit (int /*<<< orphan*/ ,int volatile*) ; 
 int /*<<< orphan*/  i_bit_set (int /*<<< orphan*/ ,int volatile*) ; 
 int /*<<< orphan*/  machine_timeout_suspended () ; 
 int rdtsc64 () ; 

void
i386_signal_cpu(int cpu, mp_event_t event, mp_sync_t mode)
{
	volatile int	*signals = &cpu_datap(cpu)->cpu_signals;
	uint64_t	tsc_timeout;

	
	if (!cpu_datap(cpu)->cpu_running)
		return;

	if (event == MP_TLB_FLUSH)
	        KERNEL_DEBUG(TRACE_MP_TLB_FLUSH | DBG_FUNC_START, cpu, 0, 0, 0, 0);

	DBGLOG(cpu_signal, cpu, event);
	
	i_bit_set(event, signals);
	i386_cpu_IPI(cpu);
	if (mode == SYNC) {
	   again:
		tsc_timeout = !machine_timeout_suspended() ?
					rdtsc64() + (1000*1000*1000) :
					~0ULL;
		while (i_bit(event, signals) && rdtsc64() < tsc_timeout) {
			cpu_pause();
		}
		if (i_bit(event, signals)) {
			DBG("i386_signal_cpu(%d, 0x%x, SYNC) timed out\n",
				cpu, event);
			goto again;
		}
	}
	if (event == MP_TLB_FLUSH)
	        KERNEL_DEBUG(TRACE_MP_TLB_FLUSH | DBG_FUNC_END, cpu, 0, 0, 0, 0);
}