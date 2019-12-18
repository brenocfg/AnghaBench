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
typedef  int u64 ;
struct niu {int flags; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ETH_DATA_LEN ; 
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  niu_init_tx_bmac (struct niu*,int,int) ; 
 int /*<<< orphan*/  niu_init_tx_xmac (struct niu*,int,int) ; 

__attribute__((used)) static void niu_init_tx_mac(struct niu *np)
{
	u64 min, max;

	min = 64;
	if (np->dev->mtu > ETH_DATA_LEN)
		max = 9216;
	else
		max = 1522;

	/* The XMAC_MIN register only accepts values for TX min which
	 * have the low 3 bits cleared.
	 */
	BUG_ON(min & 0x7);

	if (np->flags & NIU_FLAGS_XMAC)
		niu_init_tx_xmac(np, min, max);
	else
		niu_init_tx_bmac(np, min, max);
}