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
typedef  int u8 ;
struct wl12xx_vif {int last_tx_hlid; int /*<<< orphan*/  links_map; } ;
struct wl1271 {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int WL12XX_MAX_LINKS ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* wlcore_lnk_dequeue_high_prio (struct wl1271*,int,int,int*) ; 

__attribute__((used)) static struct sk_buff *wlcore_vif_dequeue_high_prio(struct wl1271 *wl,
						    struct wl12xx_vif *wlvif,
						    u8 ac, u8 *hlid,
						    u8 *low_prio_hlid)
{
	struct sk_buff *skb = NULL;
	int i, h, start_hlid;

	/* start from the link after the last one */
	start_hlid = (wlvif->last_tx_hlid + 1) % WL12XX_MAX_LINKS;

	/* dequeue according to AC, round robin on each link */
	for (i = 0; i < WL12XX_MAX_LINKS; i++) {
		h = (start_hlid + i) % WL12XX_MAX_LINKS;

		/* only consider connected stations */
		if (!test_bit(h, wlvif->links_map))
			continue;

		skb = wlcore_lnk_dequeue_high_prio(wl, h, ac,
						   low_prio_hlid);
		if (!skb)
			continue;

		wlvif->last_tx_hlid = h;
		break;
	}

	if (!skb)
		wlvif->last_tx_hlid = 0;

	*hlid = wlvif->last_tx_hlid;
	return skb;
}