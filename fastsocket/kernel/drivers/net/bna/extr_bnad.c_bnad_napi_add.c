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
typedef  size_t u32 ;
struct bnad_rx_ctrl {int /*<<< orphan*/  napi; } ;
struct bnad {int num_rxp_per_rx; int /*<<< orphan*/  netdev; TYPE_1__* rx_info; } ;
struct TYPE_2__ {struct bnad_rx_ctrl* rx_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_NAPI_POLL_QUOTA ; 
 int /*<<< orphan*/  bnad_napi_poll_rx ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnad_napi_add(struct bnad *bnad, u32 rx_id)
{
	struct bnad_rx_ctrl *rx_ctrl;
	int i;

	/* Initialize & enable NAPI */
	for (i = 0; i <	bnad->num_rxp_per_rx; i++) {
		rx_ctrl = &bnad->rx_info[rx_id].rx_ctrl[i];
		netif_napi_add(bnad->netdev, &rx_ctrl->napi,
			       bnad_napi_poll_rx, BNAD_NAPI_POLL_QUOTA);
	}
}