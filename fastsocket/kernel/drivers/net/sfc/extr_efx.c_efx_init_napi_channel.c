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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_channel {int /*<<< orphan*/  napi_str; int /*<<< orphan*/  napi_dev; struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_poll ; 
 int /*<<< orphan*/  napi_weight ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_init_napi_channel(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;

	channel->napi_dev = efx->net_dev;
	netif_napi_add(channel->napi_dev, &channel->napi_str,
		       efx_poll, napi_weight);
}