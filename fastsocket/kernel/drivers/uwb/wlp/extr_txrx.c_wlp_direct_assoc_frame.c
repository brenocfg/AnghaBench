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
struct wlp_frame_assoc {int type; } ;
struct uwb_dev_addr {int dummy; } ;
struct wlp_assoc_frame_ctx {int /*<<< orphan*/  ws; struct uwb_dev_addr src; struct sk_buff* skb; struct wlp* wlp; } ;
struct wlp {TYPE_2__* rc; } ;
struct sk_buff {scalar_t__ data; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  WLP_ASSOC_C1 131 
#define  WLP_ASSOC_C3 130 
#define  WLP_ASSOC_D1 129 
#define  WLP_ASSOC_E1 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct wlp_assoc_frame_ctx*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct wlp_assoc_frame_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_handle_c1_frame ; 
 int /*<<< orphan*/  wlp_handle_c3_frame ; 
 int /*<<< orphan*/  wlp_handle_d1_frame ; 

__attribute__((used)) static
void wlp_direct_assoc_frame(struct wlp *wlp, struct sk_buff *skb,
			   struct uwb_dev_addr *src)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	struct wlp_frame_assoc *assoc = (void *) skb->data;
	struct wlp_assoc_frame_ctx *frame_ctx;

	frame_ctx = kmalloc(sizeof(*frame_ctx), GFP_ATOMIC);
	if (frame_ctx == NULL) {
		dev_err(dev, "WLP: Unable to allocate memory for association "
			"frame handling.\n");
		kfree_skb(skb);
		return;
	}
	frame_ctx->wlp = wlp;
	frame_ctx->skb = skb;
	frame_ctx->src = *src;
	switch (assoc->type) {
	case WLP_ASSOC_D1:
		INIT_WORK(&frame_ctx->ws, wlp_handle_d1_frame);
		schedule_work(&frame_ctx->ws);
		break;
	case WLP_ASSOC_E1:
		kfree_skb(skb); /* Temporary until we handle it */
		kfree(frame_ctx); /* Temporary until we handle it */
		break;
	case WLP_ASSOC_C1:
		INIT_WORK(&frame_ctx->ws, wlp_handle_c1_frame);
		schedule_work(&frame_ctx->ws);
		break;
	case WLP_ASSOC_C3:
		INIT_WORK(&frame_ctx->ws, wlp_handle_c3_frame);
		schedule_work(&frame_ctx->ws);
		break;
	default:
		dev_err(dev, "Received unexpected association frame. "
			"Type = %d \n", assoc->type);
		kfree_skb(skb);
		kfree(frame_ctx);
		break;
	}
}