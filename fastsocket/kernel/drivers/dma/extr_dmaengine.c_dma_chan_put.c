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
struct dma_chan {scalar_t__ client_count; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* device_free_chan_resources ) (struct dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dma_chan_to_owner (struct dma_chan*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dma_chan*) ; 

__attribute__((used)) static void dma_chan_put(struct dma_chan *chan)
{
	if (!chan->client_count)
		return; /* this channel failed alloc_chan_resources */
	chan->client_count--;
	module_put(dma_chan_to_owner(chan));
	if (chan->client_count == 0)
		chan->device->device_free_chan_resources(chan);
}