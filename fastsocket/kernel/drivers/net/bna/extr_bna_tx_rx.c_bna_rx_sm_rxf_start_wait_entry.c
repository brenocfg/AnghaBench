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
struct bna_rx {int /*<<< orphan*/  rxf; TYPE_1__* bna; int /*<<< orphan*/  (* rx_post_cbfn ) (int /*<<< orphan*/ ,struct bna_rx*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_rxf_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bna_rx*) ; 

__attribute__((used)) static void bna_rx_sm_rxf_start_wait_entry(struct bna_rx *rx)
{
	rx->rx_post_cbfn(rx->bna->bnad, rx);
	bna_rxf_start(&rx->rxf);
}