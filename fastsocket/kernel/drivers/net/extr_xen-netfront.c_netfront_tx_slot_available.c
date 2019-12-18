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
struct TYPE_2__ {int req_prod_pvt; int rsp_cons; } ;
struct netfront_info {TYPE_1__ tx; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int TX_MAX_TARGET ; 

__attribute__((used)) static int netfront_tx_slot_available(struct netfront_info *np)
{
	return ((np->tx.req_prod_pvt - np->tx.rsp_cons) <
		(TX_MAX_TARGET - MAX_SKB_FRAGS - 2));
}