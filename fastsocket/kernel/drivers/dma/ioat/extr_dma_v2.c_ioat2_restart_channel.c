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
struct ioat_chan_common {int dummy; } ;
struct ioat2_dma_chan {struct ioat_chan_common base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cleanup (struct ioat2_dma_chan*,unsigned long) ; 
 int /*<<< orphan*/  __ioat2_restart_chan (struct ioat2_dma_chan*) ; 
 int /*<<< orphan*/  ioat2_quiesce (struct ioat_chan_common*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioat_cleanup_preamble (struct ioat_chan_common*,unsigned long*) ; 

__attribute__((used)) static void ioat2_restart_channel(struct ioat2_dma_chan *ioat)
{
	struct ioat_chan_common *chan = &ioat->base;
	unsigned long phys_complete;

	ioat2_quiesce(chan, 0);
	if (ioat_cleanup_preamble(chan, &phys_complete))
		__cleanup(ioat, phys_complete);

	__ioat2_restart_chan(ioat);
}