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
struct sk_buff {int* data; int len; } ;
struct btsdio_data {TYPE_2__* hdev; int /*<<< orphan*/  func; } ;
struct TYPE_6__ {int pkt_type; } ;
struct TYPE_4__ {int byte_tx; } ;
struct TYPE_5__ {TYPE_1__ stat; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_PC_WRT ; 
 int /*<<< orphan*/  REG_TDAT ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sdio_writesb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int btsdio_tx_packet(struct btsdio_data *data, struct sk_buff *skb)
{
	int err;

	BT_DBG("%s", data->hdev->name);

	/* Prepend Type-A header */
	skb_push(skb, 4);
	skb->data[0] = (skb->len & 0x0000ff);
	skb->data[1] = (skb->len & 0x00ff00) >> 8;
	skb->data[2] = (skb->len & 0xff0000) >> 16;
	skb->data[3] = bt_cb(skb)->pkt_type;

	err = sdio_writesb(data->func, REG_TDAT, skb->data, skb->len);
	if (err < 0) {
		skb_pull(skb, 4);
		sdio_writeb(data->func, 0x01, REG_PC_WRT, NULL);
		return err;
	}

	data->hdev->stat.byte_tx += skb->len;

	kfree_skb(skb);

	return 0;
}