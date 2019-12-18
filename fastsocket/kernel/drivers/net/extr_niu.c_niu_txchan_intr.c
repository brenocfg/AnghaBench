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
struct tx_ring_info {scalar_t__ tx_cs; int /*<<< orphan*/  tx_channel; } ;
struct niu {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  TX_CS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niudbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ nr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_txchan_intr(struct niu *np, struct tx_ring_info *rp,
			    int ldn)
{
	rp->tx_cs = nr64(TX_CS(rp->tx_channel));

	niudbg(INTR, "%s: txchan_intr cs[%llx]\n",
	       np->dev->name, (unsigned long long) rp->tx_cs);
}