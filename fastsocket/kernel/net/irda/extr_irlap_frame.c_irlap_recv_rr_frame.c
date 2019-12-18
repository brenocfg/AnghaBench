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
struct sk_buff {int* data; } ;
struct irlap_info {int nr; } ;
struct irlap_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECV_RR_CMD ; 
 int /*<<< orphan*/  RECV_RR_RSP ; 
 int /*<<< orphan*/  irlap_do_event (struct irlap_cb*,int /*<<< orphan*/ ,struct sk_buff*,struct irlap_info*) ; 

__attribute__((used)) static inline void irlap_recv_rr_frame(struct irlap_cb *self,
				       struct sk_buff *skb,
				       struct irlap_info *info, int command)
{
	info->nr = skb->data[1] >> 5;

	/* Check if this is a command or a response frame */
	if (command)
		irlap_do_event(self, RECV_RR_CMD, skb, info);
	else
		irlap_do_event(self, RECV_RR_RSP, skb, info);
}