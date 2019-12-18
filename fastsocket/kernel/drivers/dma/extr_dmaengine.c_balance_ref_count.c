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
struct module {int dummy; } ;
struct dma_chan {scalar_t__ client_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __module_get (struct module*) ; 
 struct module* dma_chan_to_owner (struct dma_chan*) ; 
 scalar_t__ dmaengine_ref_count ; 

__attribute__((used)) static void balance_ref_count(struct dma_chan *chan)
{
	struct module *owner = dma_chan_to_owner(chan);

	while (chan->client_count < dmaengine_ref_count) {
		__module_get(owner);
		chan->client_count++;
	}
}