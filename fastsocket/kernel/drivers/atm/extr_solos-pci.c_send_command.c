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
struct solos_card {TYPE_1__* dev; } ;
struct sk_buff {int dummy; } ;
struct pkt_hdr {void* type; void* vci; void* vpi; void* size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t PKT_COMMAND ; 
 struct sk_buff* alloc_skb (size_t,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fpga_queue (struct solos_card*,int,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 scalar_t__ skb_put (struct sk_buff*,size_t) ; 

__attribute__((used)) static int send_command(struct solos_card *card, int dev, const char *buf, size_t size)
{
	struct sk_buff *skb;
	struct pkt_hdr *header;

	if (size > (BUF_SIZE - sizeof(*header))) {
		dev_dbg(&card->dev->dev, "Command is too big.  Dropping request\n");
		return 0;
	}
	skb = alloc_skb(size + sizeof(*header), GFP_ATOMIC);
	if (!skb) {
		dev_warn(&card->dev->dev, "Failed to allocate sk_buff in send_command()\n");
		return 0;
	}

	header = (void *)skb_put(skb, sizeof(*header));

	header->size = cpu_to_le16(size);
	header->vpi = cpu_to_le16(0);
	header->vci = cpu_to_le16(0);
	header->type = cpu_to_le16(PKT_COMMAND);

	memcpy(skb_put(skb, size), buf, size);

	fpga_queue(card, dev, skb, NULL);

	return 0;
}