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
struct efx_channel {int work_pending; int enabled; int /*<<< orphan*/  napi_str; int /*<<< orphan*/  channel; TYPE_1__* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_eventq_read_ack (struct efx_channel*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void efx_start_eventq(struct efx_channel *channel)
{
	netif_dbg(channel->efx, ifup, channel->efx->net_dev,
		  "chan %d start event queue\n", channel->channel);

	/* The interrupt handler for this channel may set work_pending
	 * as soon as we enable it.  Make sure it's cleared before
	 * then.  Similarly, make sure it sees the enabled flag set.
	 */
	channel->work_pending = false;
	channel->enabled = true;
	smp_wmb();

	napi_enable(&channel->napi_str);
	efx_nic_eventq_read_ack(channel);
}