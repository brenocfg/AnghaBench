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
struct h4_struct {int rx_count; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  rx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  H4_W4_DATA ; 
 int /*<<< orphan*/  H4_W4_PACKET_TYPE ; 
 int /*<<< orphan*/  hci_recv_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int skb_tailroom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int h4_check_data_len(struct h4_struct *h4, int len)
{
	register int room = skb_tailroom(h4->rx_skb);

	BT_DBG("len %d room %d", len, room);

	if (!len) {
		hci_recv_frame(h4->rx_skb);
	} else if (len > room) {
		BT_ERR("Data length is too large");
		kfree_skb(h4->rx_skb);
	} else {
		h4->rx_state = H4_W4_DATA;
		h4->rx_count = len;
		return len;
	}

	h4->rx_state = H4_W4_PACKET_TYPE;
	h4->rx_skb   = NULL;
	h4->rx_count = 0;

	return 0;
}