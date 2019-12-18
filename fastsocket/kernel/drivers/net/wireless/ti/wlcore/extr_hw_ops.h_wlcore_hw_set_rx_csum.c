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
struct wl1271_rx_descriptor {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_rx_csum ) (struct wl1271*,struct wl1271_rx_descriptor*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wl1271*,struct wl1271_rx_descriptor*,struct sk_buff*) ; 

__attribute__((used)) static inline void
wlcore_hw_set_rx_csum(struct wl1271 *wl,
		      struct wl1271_rx_descriptor *desc,
		      struct sk_buff *skb)
{
	if (wl->ops->set_rx_csum)
		wl->ops->set_rx_csum(wl, desc, skb);
}