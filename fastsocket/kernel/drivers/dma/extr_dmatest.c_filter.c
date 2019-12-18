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
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmatest_match_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  dmatest_match_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool filter(struct dma_chan *chan, void *param)
{
	if (!dmatest_match_channel(chan) || !dmatest_match_device(chan->device))
		return false;
	else
		return true;
}