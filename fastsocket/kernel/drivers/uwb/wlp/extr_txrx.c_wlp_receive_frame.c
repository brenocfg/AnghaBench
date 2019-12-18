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
struct wlp_frame_std_abbrv_hdr {int dummy; } ;
struct wlp_frame_hdr {int type; int /*<<< orphan*/  mux_hdr; } ;
struct wlp_frame_assoc {int dummy; } ;
struct wlp {int dummy; } ;
struct uwb_dev_addr {int /*<<< orphan*/ * data; } ;
struct sk_buff {unsigned int len; void* data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WLP_FRAME_ABBREVIATED 131 
#define  WLP_FRAME_ASSOCIATION 130 
#define  WLP_FRAME_CONTROL 129 
#define  WLP_FRAME_STANDARD 128 
 scalar_t__ WLP_PROTOCOL_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_ratelimit () ; 
 int /*<<< orphan*/  wlp_receive_assoc_frame (struct wlp*,struct sk_buff*,struct uwb_dev_addr*) ; 
 int wlp_verify_prep_rx_frame (struct wlp*,struct sk_buff*,struct uwb_dev_addr*) ; 

int wlp_receive_frame(struct device *dev, struct wlp *wlp, struct sk_buff *skb,
		      struct uwb_dev_addr *src)
{
	unsigned len = skb->len;
	void *ptr = skb->data;
	struct wlp_frame_hdr *hdr;
	int result = 0;

	if (len < sizeof(*hdr)) {
		dev_err(dev, "Not enough data to parse WLP header.\n");
		result = -EINVAL;
		goto out;
	}
	hdr = ptr;
	if (le16_to_cpu(hdr->mux_hdr) != WLP_PROTOCOL_ID) {
		dev_err(dev, "Not a WLP frame type.\n");
		result = -EINVAL;
		goto out;
	}
	switch (hdr->type) {
	case WLP_FRAME_STANDARD:
		if (len < sizeof(struct wlp_frame_std_abbrv_hdr)) {
			dev_err(dev, "Not enough data to parse Standard "
				"WLP header.\n");
			goto out;
		}
		result = wlp_verify_prep_rx_frame(wlp, skb, src);
		if (result < 0) {
			if (printk_ratelimit())
				dev_err(dev, "WLP: Verification of frame "
					"from neighbor %02x:%02x failed.\n",
					src->data[1], src->data[0]);
			goto out;
		}
		result = 1;
		break;
	case WLP_FRAME_ABBREVIATED:
		dev_err(dev, "Abbreviated frame received. FIXME?\n");
		kfree_skb(skb);
		break;
	case WLP_FRAME_CONTROL:
		dev_err(dev, "Control frame received. FIXME?\n");
		kfree_skb(skb);
		break;
	case WLP_FRAME_ASSOCIATION:
		if (len < sizeof(struct wlp_frame_assoc)) {
			dev_err(dev, "Not enough data to parse Association "
				"WLP header.\n");
			goto out;
		}
		wlp_receive_assoc_frame(wlp, skb, src);
		break;
	default:
		dev_err(dev, "Invalid frame received.\n");
		result = -EINVAL;
		break;
	}
out:
	if (result < 0) {
		kfree_skb(skb);
		result = 0;
	}
	return result;
}