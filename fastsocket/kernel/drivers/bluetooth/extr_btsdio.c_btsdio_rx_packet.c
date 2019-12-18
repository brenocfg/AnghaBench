#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int* data; void* dev; } ;
struct btsdio_data {int /*<<< orphan*/  func; TYPE_2__* hdev; } ;
struct TYPE_6__ {int pkt_type; } ;
struct TYPE_4__ {int byte_rx; } ;
struct TYPE_5__ {TYPE_1__ stat; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REG_PC_RRT ; 
 int /*<<< orphan*/  REG_RDAT ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int hci_recv_frame (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int sdio_readsb (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int btsdio_rx_packet(struct btsdio_data *data)
{
	u8 hdr[4] __attribute__ ((aligned(4)));
	struct sk_buff *skb;
	int err, len;

	BT_DBG("%s", data->hdev->name);

	err = sdio_readsb(data->func, hdr, REG_RDAT, 4);
	if (err < 0)
		return err;

	len = hdr[0] | (hdr[1] << 8) | (hdr[2] << 16);
	if (len < 4 || len > 65543)
		return -EILSEQ;

	skb = bt_skb_alloc(len - 4, GFP_KERNEL);
	if (!skb) {
		/* Out of memory. Prepare a read retry and just
		 * return with the expectation that the next time
		 * we're called we'll have more memory. */
		return -ENOMEM;
	}

	skb_put(skb, len - 4);

	err = sdio_readsb(data->func, skb->data, REG_RDAT, len - 4);
	if (err < 0) {
		kfree_skb(skb);
		return err;
	}

	data->hdev->stat.byte_rx += len;

	skb->dev = (void *) data->hdev;
	bt_cb(skb)->pkt_type = hdr[3];

	err = hci_recv_frame(skb);
	if (err < 0)
		return err;

	sdio_writeb(data->func, 0x00, REG_PC_RRT, NULL);

	return 0;
}