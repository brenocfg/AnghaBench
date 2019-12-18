#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tg3 {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  tg3_napi_disable (struct tg3*) ; 

__attribute__((used)) static inline void tg3_netif_stop(struct tg3 *tp)
{
	tp->dev->trans_start = jiffies;	/* prevent tx timeout */
	tg3_napi_disable(tp);
	netif_carrier_off(tp->dev);
	netif_tx_disable(tp->dev);
}