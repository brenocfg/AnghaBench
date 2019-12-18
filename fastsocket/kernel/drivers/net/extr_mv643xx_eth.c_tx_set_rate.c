#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mv643xx_eth_private {TYPE_2__* shared; TYPE_1__* dev; } ;
struct TYPE_4__ {int t_clk; int tx_bw_control; } ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_BW_BURST ; 
 int /*<<< orphan*/  TX_BW_BURST_MOVED ; 
#define  TX_BW_CONTROL_NEW_LAYOUT 129 
#define  TX_BW_CONTROL_OLD_LAYOUT 128 
 int /*<<< orphan*/  TX_BW_MTU ; 
 int /*<<< orphan*/  TX_BW_MTU_MOVED ; 
 int /*<<< orphan*/  TX_BW_RATE ; 
 int /*<<< orphan*/  TX_BW_RATE_MOVED ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tx_set_rate(struct mv643xx_eth_private *mp, int rate, int burst)
{
	int token_rate;
	int mtu;
	int bucket_size;

	token_rate = ((rate / 1000) * 64) / (mp->shared->t_clk / 1000);
	if (token_rate > 1023)
		token_rate = 1023;

	mtu = (mp->dev->mtu + 255) >> 8;
	if (mtu > 63)
		mtu = 63;

	bucket_size = (burst + 255) >> 8;
	if (bucket_size > 65535)
		bucket_size = 65535;

	switch (mp->shared->tx_bw_control) {
	case TX_BW_CONTROL_OLD_LAYOUT:
		wrlp(mp, TX_BW_RATE, token_rate);
		wrlp(mp, TX_BW_MTU, mtu);
		wrlp(mp, TX_BW_BURST, bucket_size);
		break;
	case TX_BW_CONTROL_NEW_LAYOUT:
		wrlp(mp, TX_BW_RATE_MOVED, token_rate);
		wrlp(mp, TX_BW_MTU_MOVED, mtu);
		wrlp(mp, TX_BW_BURST_MOVED, bucket_size);
		break;
	}
}