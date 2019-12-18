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
struct ll_struct {int rx_count; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  rx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  HCILL_W4_DATA ; 
 int /*<<< orphan*/  HCILL_W4_PACKET_TYPE ; 
 int /*<<< orphan*/  hci_recv_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int skb_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ll_check_data_len(struct ll_struct *ll, int len)
{
	register int room = skb_tailroom(ll->rx_skb);

	BT_DBG("len %d room %d", len, room);

	if (!len) {
		hci_recv_frame(ll->rx_skb);
	} else if (len > room) {
		BT_ERR("Data length is too large");
		kfree_skb(ll->rx_skb);
	} else {
		ll->rx_state = HCILL_W4_DATA;
		ll->rx_count = len;
		return len;
	}

	ll->rx_state = HCILL_W4_PACKET_TYPE;
	ll->rx_skb   = NULL;
	ll->rx_count = 0;

	return 0;
}