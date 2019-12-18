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
struct sk_buff {TYPE_1__* dev; } ;
struct llc_xid_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int /*<<< orphan*/  LLC_XID_NULL_CLASS_2 ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* llc_alloc_frame (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_xid_cmd (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  llc_station_send_pdu (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int llc_station_ac_send_null_dsap_xid_c(struct sk_buff *skb)
{
	int rc = 1;
	struct sk_buff *nskb = llc_alloc_frame(NULL, skb->dev, LLC_PDU_TYPE_U,
					       sizeof(struct llc_xid_info));

	if (!nskb)
		goto out;
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, 0, 0, LLC_PDU_CMD);
	llc_pdu_init_as_xid_cmd(nskb, LLC_XID_NULL_CLASS_2, 127);
	rc = llc_mac_hdr_init(nskb, skb->dev->dev_addr, skb->dev->dev_addr);
	if (unlikely(rc))
		goto free;
	llc_station_send_pdu(nskb);
out:
	return rc;
free:
	kfree_skb(skb);
	goto out;
}