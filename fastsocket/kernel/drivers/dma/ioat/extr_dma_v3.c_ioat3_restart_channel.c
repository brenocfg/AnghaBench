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
typedef  int /*<<< orphan*/  u32 ;
struct ioat_chan_common {int dummy; } ;
struct ioat2_dma_chan {struct ioat_chan_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cleanup (struct ioat2_dma_chan*,unsigned long) ; 
 int /*<<< orphan*/  __ioat2_restart_chan (struct ioat2_dma_chan*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ioat_chansts (struct ioat_chan_common*) ; 
 scalar_t__ ioat_cleanup_preamble (struct ioat_chan_common*,unsigned long*) ; 
 int /*<<< orphan*/  ioat_suspend (struct ioat_chan_common*) ; 
 scalar_t__ is_ioat_active (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ioat_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ioat3_restart_channel(struct ioat2_dma_chan *ioat)
{
	struct ioat_chan_common *chan = &ioat->base;
	unsigned long phys_complete;
	u32 status;

	status = ioat_chansts(chan);
	if (is_ioat_active(status) || is_ioat_idle(status))
		ioat_suspend(chan);
	while (is_ioat_active(status) || is_ioat_idle(status)) {
		status = ioat_chansts(chan);
		cpu_relax();
	}

	if (ioat_cleanup_preamble(chan, &phys_complete))
		__cleanup(ioat, phys_complete);

	__ioat2_restart_chan(ioat);
}