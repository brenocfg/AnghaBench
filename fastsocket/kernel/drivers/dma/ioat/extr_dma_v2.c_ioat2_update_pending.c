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
struct ioat2_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ioat2_issue_pending (struct ioat2_dma_chan*) ; 
 scalar_t__ ioat2_ring_pending (struct ioat2_dma_chan*) ; 
 scalar_t__ ioat_pending_level ; 

__attribute__((used)) static void ioat2_update_pending(struct ioat2_dma_chan *ioat)
{
	if (ioat2_ring_pending(ioat) > ioat_pending_level)
		__ioat2_issue_pending(ioat);
}