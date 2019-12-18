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
struct idmac_channel {int /*<<< orphan*/  chan_mutex; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __idmac_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 

__attribute__((used)) static void idmac_terminate_all(struct dma_chan *chan)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);

	mutex_lock(&ichan->chan_mutex);

	__idmac_terminate_all(chan);

	mutex_unlock(&ichan->chan_mutex);
}