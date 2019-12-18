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
typedef  int u32 ;
struct TYPE_2__ {int rx_missed_errors; } ;
struct de_private {TYPE_1__ net_stats; } ;

/* Variables and functions */
 int RxMissedMask ; 
 int RxMissedOver ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void de_rx_missed(struct de_private *de, u32 rx_missed)
{
	if (unlikely(rx_missed & RxMissedOver))
		de->net_stats.rx_missed_errors += RxMissedMask;
	else
		de->net_stats.rx_missed_errors += (rx_missed & RxMissedMask);
}