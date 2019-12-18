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
struct wl1271 {int num_tx_desc; int /*<<< orphan*/  tx_frames_cnt; struct sk_buff** tx_frames; int /*<<< orphan*/  tx_frames_map; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl1271_alloc_tx_id(struct wl1271 *wl, struct sk_buff *skb)
{
	int id;

	id = find_first_zero_bit(wl->tx_frames_map, wl->num_tx_desc);
	if (id >= wl->num_tx_desc)
		return -EBUSY;

	__set_bit(id, wl->tx_frames_map);
	wl->tx_frames[id] = skb;
	wl->tx_frames_cnt++;
	return id;
}