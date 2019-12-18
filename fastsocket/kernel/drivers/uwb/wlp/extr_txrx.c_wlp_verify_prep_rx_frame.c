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
struct wlp_frame_std_abbrv_hdr {scalar_t__ tag; } ;
struct wlp_eda_node {scalar_t__ tag; scalar_t__ state; } ;
struct wlp {int /*<<< orphan*/  eda; TYPE_2__* rc; } ;
struct uwb_dev_addr {int /*<<< orphan*/ * data; } ;
struct sk_buff {scalar_t__ data; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WLP_WSS_CONNECTED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int wlp_copy_eda_node (int /*<<< orphan*/ *,struct uwb_dev_addr*,struct wlp_eda_node*) ; 

__attribute__((used)) static
int wlp_verify_prep_rx_frame(struct wlp *wlp, struct sk_buff *skb,
			     struct uwb_dev_addr *src)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	int result = -EINVAL;
	struct wlp_eda_node eda_entry;
	struct wlp_frame_std_abbrv_hdr *hdr = (void *) skb->data;

	/*verify*/
	result = wlp_copy_eda_node(&wlp->eda, src, &eda_entry);
	if (result < 0) {
		if (printk_ratelimit())
			dev_err(dev, "WLP: Incoming frame is from unknown "
				"neighbor %02x:%02x.\n", src->data[1],
				src->data[0]);
		goto out;
	}
	if (hdr->tag != eda_entry.tag) {
		if (printk_ratelimit())
			dev_err(dev, "WLP: Tag of incoming frame from "
				"%02x:%02x does not match expected tag. "
				"Received 0x%02x, expected 0x%02x. \n",
				src->data[1], src->data[0], hdr->tag,
				eda_entry.tag);
		result = -EINVAL;
		goto out;
	}
	if (eda_entry.state != WLP_WSS_CONNECTED) {
		if (printk_ratelimit())
			dev_err(dev, "WLP: Incoming frame from "
				"%02x:%02x does is not from connected WSS.\n",
				src->data[1], src->data[0]);
		result = -EINVAL;
		goto out;
	}
	/*prep*/
	skb_pull(skb, sizeof(*hdr));
out:
	return result;
}