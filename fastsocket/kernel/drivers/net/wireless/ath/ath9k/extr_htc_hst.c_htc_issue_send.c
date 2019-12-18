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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct htc_target {int /*<<< orphan*/  hif_dev; TYPE_1__* hif; struct htc_endpoint* endpoint; } ;
struct htc_frame_hdr {size_t endpoint_id; size_t flags; int /*<<< orphan*/  payload_len; } ;
struct htc_endpoint {int /*<<< orphan*/  ul_pipeid; } ;
struct TYPE_2__ {int (* send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int htc_issue_send(struct htc_target *target, struct sk_buff* skb,
			  u16 len, u8 flags, u8 epid)

{
	struct htc_frame_hdr *hdr;
	struct htc_endpoint *endpoint = &target->endpoint[epid];
	int status;

	hdr = (struct htc_frame_hdr *)
		skb_push(skb, sizeof(struct htc_frame_hdr));
	hdr->endpoint_id = epid;
	hdr->flags = flags;
	hdr->payload_len = cpu_to_be16(len);

	status = target->hif->send(target->hif_dev, endpoint->ul_pipeid, skb);

	return status;
}