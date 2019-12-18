#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct solos_card {TYPE_1__* dev; } ;
struct sk_buff {int dummy; } ;
struct pkt_hdr {void* type; void* vci; void* vpi; void* size; } ;
struct atm_vcc {int /*<<< orphan*/  flags; TYPE_2__* dev; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; } ;
struct TYPE_4__ {struct solos_card* dev_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PKT_PCLOSE ; 
 int /*<<< orphan*/  SOLOS_CHAN (TYPE_2__*) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fpga_queue (struct solos_card*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void pclose(struct atm_vcc *vcc)
{
	struct solos_card *card = vcc->dev->dev_data;
	struct sk_buff *skb;
	struct pkt_hdr *header;

	skb = alloc_skb(sizeof(*header), GFP_ATOMIC);
	if (!skb) {
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in pclose()\n");
		return;
	}
	header = (void *)skb_put(skb, sizeof(*header));

	header->size = cpu_to_le16(0);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_PCLOSE);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, NULL);

	clear_bit(ATM_VF_ADDR, &vcc->flags);
	clear_bit(ATM_VF_READY, &vcc->flags);

	return;
}