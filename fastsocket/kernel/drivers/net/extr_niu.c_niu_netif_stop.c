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
struct niu {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_tx_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  niu_disable_napi (struct niu*) ; 

__attribute__((used)) static void niu_netif_stop(struct niu *np)
{
	np->dev->trans_start = jiffies;	/* prevent tx timeout */

	niu_disable_napi(np);

	netif_tx_disable(np->dev);
}