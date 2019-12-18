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
struct TYPE_2__ {unsigned int rx_bytes; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; } ;
struct net_local {TYPE_1__ MacStat; } ;

/* Variables and functions */
 unsigned char GROUP_BIT ; 

__attribute__((used)) static void tms380tr_update_rcv_stats(struct net_local *tp, unsigned char DataPtr[],
					unsigned int Length)
{
	tp->MacStat.rx_packets++;
	tp->MacStat.rx_bytes += Length;
	
	/* Test functional bit */
	if(DataPtr[2] & GROUP_BIT)
		tp->MacStat.multicast++;

	return;
}