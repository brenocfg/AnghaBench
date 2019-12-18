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
typedef  int /*<<< orphan*/  u32 ;
struct spider_net_hw_descr {int dmac_cmd_status; scalar_t__ next_descr_addr; int /*<<< orphan*/  data_error; int /*<<< orphan*/  data_status; int /*<<< orphan*/  valid_size; int /*<<< orphan*/  result_size; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_addr; } ;
struct spider_net_descr_chain {int num_desc; struct spider_net_descr* ring; struct spider_net_descr* head; struct spider_net_descr* tail; } ;
struct spider_net_descr {struct spider_net_descr* next; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  skb; struct spider_net_hw_descr* hwdescr; } ;
struct spider_net_card {TYPE_1__* netdev; struct spider_net_descr_chain rx_chain; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_GDACNEXTDA ; 
 int /*<<< orphan*/  SPIDER_NET_GDACTDPA ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int spider_net_get_descr_status (struct spider_net_hw_descr*) ; 
 int /*<<< orphan*/  spider_net_read_reg (struct spider_net_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_rx_chain(struct spider_net_card *card)
{
	struct spider_net_descr_chain *chain = &card->rx_chain;
	struct spider_net_descr *start= chain->tail;
	struct spider_net_descr *descr= start;
	struct spider_net_hw_descr *hwd = start->hwdescr;
	struct device *dev = &card->netdev->dev;
	u32 curr_desc, next_desc;
	int status;

	int tot = 0;
	int cnt = 0;
	int off = start - chain->ring;
	int cstat = hwd->dmac_cmd_status;

	dev_info(dev, "Total number of descrs=%d\n",
		chain->num_desc);
	dev_info(dev, "Chain tail located at descr=%d, status=0x%x\n",
		off, cstat);

	curr_desc = spider_net_read_reg(card, SPIDER_NET_GDACTDPA);
	next_desc = spider_net_read_reg(card, SPIDER_NET_GDACNEXTDA);

	status = cstat;
	do
	{
		hwd = descr->hwdescr;
		off = descr - chain->ring;
		status = hwd->dmac_cmd_status;

		if (descr == chain->head)
			dev_info(dev, "Chain head is at %d, head status=0x%x\n",
			         off, status);

		if (curr_desc == descr->bus_addr)
			dev_info(dev, "HW curr desc (GDACTDPA) is at %d, status=0x%x\n",
			         off, status);

		if (next_desc == descr->bus_addr)
			dev_info(dev, "HW next desc (GDACNEXTDA) is at %d, status=0x%x\n",
			         off, status);

		if (hwd->next_descr_addr == 0)
			dev_info(dev, "chain is cut at %d\n", off);

		if (cstat != status) {
			int from = (chain->num_desc + off - cnt) % chain->num_desc;
			int to = (chain->num_desc + off - 1) % chain->num_desc;
			dev_info(dev, "Have %d (from %d to %d) descrs "
			         "with stat=0x%08x\n", cnt, from, to, cstat);
			cstat = status;
			cnt = 0;
		}

		cnt ++;
		tot ++;
		descr = descr->next;
	} while (descr != start);

	dev_info(dev, "Last %d descrs with stat=0x%08x "
	         "for a total of %d descrs\n", cnt, cstat, tot);

#ifdef DEBUG
	/* Now dump the whole ring */
	descr = start;
	do
	{
		struct spider_net_hw_descr *hwd = descr->hwdescr;
		status = spider_net_get_descr_status(hwd);
		cnt = descr - chain->ring;
		dev_info(dev, "Descr %d stat=0x%08x skb=%p\n",
		         cnt, status, descr->skb);
		dev_info(dev, "bus addr=%08x buf addr=%08x sz=%d\n",
		         descr->bus_addr, hwd->buf_addr, hwd->buf_size);
		dev_info(dev, "next=%08x result sz=%d valid sz=%d\n",
		         hwd->next_descr_addr, hwd->result_size,
		         hwd->valid_size);
		dev_info(dev, "dmac=%08x data stat=%08x data err=%08x\n",
		         hwd->dmac_cmd_status, hwd->data_status,
		         hwd->data_error);
		dev_info(dev, "\n");

		descr = descr->next;
	} while (descr != start);
#endif

}