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
struct sk_buff {scalar_t__ data; } ;
struct ar9170 {int dummy; } ;
struct TYPE_2__ {scalar_t__ phy_control; } ;
struct _carl9170_tx_superframe {TYPE_1__ f; } ;

/* Variables and functions */

__attribute__((used)) static bool carl9170_tx_rate_check(struct ar9170 *ar, struct sk_buff *_dest,
				   struct sk_buff *_src)
{
	struct _carl9170_tx_superframe *dest, *src;

	dest = (void *) _dest->data;
	src = (void *) _src->data;

	/*
	 * The mac80211 rate control algorithm expects that all MPDUs in
	 * an AMPDU share the same tx vectors.
	 * This is not really obvious right now, because the hardware
	 * does the AMPDU setup according to its own rulebook.
	 * Our nicely assembled, strictly monotonic increasing mpdu
	 * chains will be broken up, mashed back together...
	 */

	return (dest->f.phy_control == src->f.phy_control);
}