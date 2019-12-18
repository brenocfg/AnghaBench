#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 rtl8169_tx_vlan_tag(struct rtl8169_private *tp,
				      struct sk_buff *skb)
{
	return 0;
}