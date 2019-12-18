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
typedef  scalar_t__ uint32_t ;
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_seq; } ;
struct iscsi_uevent {scalar_t__ type; int iferror; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int ESRCH ; 
 scalar_t__ ISCSI_KEVENT_IF_ERROR ; 
 scalar_t__ ISCSI_UEVENT_GET_CHAP ; 
 scalar_t__ ISCSI_UEVENT_GET_STATS ; 
 scalar_t__ NLMSG_ALIGN (scalar_t__) ; 
 struct iscsi_uevent* NLMSG_DATA (struct nlmsghdr*) ; 
 scalar_t__ NLMSG_SPACE (int /*<<< orphan*/ ) ; 
 int iscsi_if_recv_msg (struct sk_buff*,struct nlmsghdr*,scalar_t__*) ; 
 int iscsi_if_send_reply (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iscsi_uevent*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  rx_queue_mutex ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void
iscsi_if_rx(struct sk_buff *skb)
{
	mutex_lock(&rx_queue_mutex);
	while (skb->len >= NLMSG_SPACE(0)) {
		int err;
		uint32_t rlen;
		struct nlmsghdr	*nlh;
		struct iscsi_uevent *ev;
		uint32_t group;

		nlh = nlmsg_hdr(skb);
		if (nlh->nlmsg_len < sizeof(*nlh) ||
		    skb->len < nlh->nlmsg_len) {
			break;
		}

		ev = NLMSG_DATA(nlh);
		rlen = NLMSG_ALIGN(nlh->nlmsg_len);
		if (rlen > skb->len)
			rlen = skb->len;

		err = iscsi_if_recv_msg(skb, nlh, &group);
		if (err) {
			ev->type = ISCSI_KEVENT_IF_ERROR;
			ev->iferror = err;
		}
		do {
			/*
			 * special case for GET_STATS:
			 * on success - sending reply and stats from
			 * inside of if_recv_msg(),
			 * on error - fall through.
			 */
			if (ev->type == ISCSI_UEVENT_GET_STATS && !err)
				break;
			if (ev->type == ISCSI_UEVENT_GET_CHAP && !err)
				break;
			err = iscsi_if_send_reply(group, nlh->nlmsg_seq,
				nlh->nlmsg_type, 0, 0, ev, sizeof(*ev));
		} while (err < 0 && err != -ECONNREFUSED && err != -ESRCH);
		skb_pull(skb, rlen);
	}
	mutex_unlock(&rx_queue_mutex);
}