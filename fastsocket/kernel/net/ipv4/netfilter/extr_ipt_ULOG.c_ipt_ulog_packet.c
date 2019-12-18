#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t data_len; unsigned int hook; char* prefix; scalar_t__ mac_len; char* indev_name; char* outdev_name; int /*<<< orphan*/  payload; int /*<<< orphan*/  mac; int /*<<< orphan*/  mark; int /*<<< orphan*/  timestamp_usec; int /*<<< orphan*/  timestamp_sec; } ;
typedef  TYPE_1__ ulog_packet_msg_t ;
struct TYPE_10__ {scalar_t__ expires; } ;
struct TYPE_9__ {int qlen; TYPE_4__ timer; struct nlmsghdr* lastnlh; void* skb; } ;
typedef  TYPE_2__ ulog_buff_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {scalar_t__ tv64; } ;
struct sk_buff {size_t len; scalar_t__ mac_header; scalar_t__ network_header; int /*<<< orphan*/  mark; TYPE_5__ tstamp; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_flags; } ;
struct net_device {scalar_t__ hard_header_len; char const* name; } ;
struct ipt_ulog_info {size_t copy_range; int qthreshold; char* prefix; int /*<<< orphan*/  nl_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int HZ ; 
 TYPE_1__* NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_DONE ; 
 struct nlmsghdr* NLMSG_PUT (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 size_t NLMSG_SPACE (int) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  PRINTR (char*) ; 
 scalar_t__ ULOG_MAC_LEN ; 
 int /*<<< orphan*/  ULOG_NL_EVENT ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int flushtimeout ; 
 scalar_t__ jiffies ; 
 struct timeval ktime_to_timeval (TYPE_5__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_copy_bits (struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff const*) ; 
 size_t skb_tailroom (void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  timer_pending (TYPE_4__*) ; 
 void* ulog_alloc_skb (size_t) ; 
 TYPE_2__* ulog_buffers ; 
 int /*<<< orphan*/  ulog_lock ; 
 int /*<<< orphan*/  ulog_send (unsigned int) ; 

__attribute__((used)) static void ipt_ulog_packet(unsigned int hooknum,
			    const struct sk_buff *skb,
			    const struct net_device *in,
			    const struct net_device *out,
			    const struct ipt_ulog_info *loginfo,
			    const char *prefix)
{
	ulog_buff_t *ub;
	ulog_packet_msg_t *pm;
	size_t size, copy_len;
	struct nlmsghdr *nlh;
	struct timeval tv;

	/* ffs == find first bit set, necessary because userspace
	 * is already shifting groupnumber, but we need unshifted.
	 * ffs() returns [1..32], we need [0..31] */
	unsigned int groupnum = ffs(loginfo->nl_group) - 1;

	/* calculate the size of the skb needed */
	if (loginfo->copy_range == 0 || loginfo->copy_range > skb->len)
		copy_len = skb->len;
	else
		copy_len = loginfo->copy_range;

	size = NLMSG_SPACE(sizeof(*pm) + copy_len);

	ub = &ulog_buffers[groupnum];

	spin_lock_bh(&ulog_lock);

	if (!ub->skb) {
		if (!(ub->skb = ulog_alloc_skb(size)))
			goto alloc_failure;
	} else if (ub->qlen >= loginfo->qthreshold ||
		   size > skb_tailroom(ub->skb)) {
		/* either the queue len is too high or we don't have
		 * enough room in nlskb left. send it to userspace. */

		ulog_send(groupnum);

		if (!(ub->skb = ulog_alloc_skb(size)))
			goto alloc_failure;
	}

	pr_debug("ipt_ULOG: qlen %d, qthreshold %Zu\n", ub->qlen,
		 loginfo->qthreshold);

	/* NLMSG_PUT contains a hidden goto nlmsg_failure !!! */
	nlh = NLMSG_PUT(ub->skb, 0, ub->qlen, ULOG_NL_EVENT,
			sizeof(*pm)+copy_len);
	ub->qlen++;

	pm = NLMSG_DATA(nlh);

	/* We might not have a timestamp, get one */
	if (skb->tstamp.tv64 == 0)
		__net_timestamp((struct sk_buff *)skb);

	/* copy hook, prefix, timestamp, payload, etc. */
	pm->data_len = copy_len;
	tv = ktime_to_timeval(skb->tstamp);
	put_unaligned(tv.tv_sec, &pm->timestamp_sec);
	put_unaligned(tv.tv_usec, &pm->timestamp_usec);
	put_unaligned(skb->mark, &pm->mark);
	pm->hook = hooknum;
	if (prefix != NULL)
		strncpy(pm->prefix, prefix, sizeof(pm->prefix));
	else if (loginfo->prefix[0] != '\0')
		strncpy(pm->prefix, loginfo->prefix, sizeof(pm->prefix));
	else
		*(pm->prefix) = '\0';

	if (in && in->hard_header_len > 0
	    && skb->mac_header != skb->network_header
	    && in->hard_header_len <= ULOG_MAC_LEN) {
		memcpy(pm->mac, skb_mac_header(skb), in->hard_header_len);
		pm->mac_len = in->hard_header_len;
	} else
		pm->mac_len = 0;

	if (in)
		strncpy(pm->indev_name, in->name, sizeof(pm->indev_name));
	else
		pm->indev_name[0] = '\0';

	if (out)
		strncpy(pm->outdev_name, out->name, sizeof(pm->outdev_name));
	else
		pm->outdev_name[0] = '\0';

	/* copy_len <= skb->len, so can't fail. */
	if (skb_copy_bits(skb, 0, pm->payload, copy_len) < 0)
		BUG();

	/* check if we are building multi-part messages */
	if (ub->qlen > 1)
		ub->lastnlh->nlmsg_flags |= NLM_F_MULTI;

	ub->lastnlh = nlh;

	/* if timer isn't already running, start it */
	if (!timer_pending(&ub->timer)) {
		ub->timer.expires = jiffies + flushtimeout * HZ / 100;
		add_timer(&ub->timer);
	}

	/* if threshold is reached, send message to userspace */
	if (ub->qlen >= loginfo->qthreshold) {
		if (loginfo->qthreshold > 1)
			nlh->nlmsg_type = NLMSG_DONE;
		ulog_send(groupnum);
	}

	spin_unlock_bh(&ulog_lock);

	return;

nlmsg_failure:
	PRINTR("ipt_ULOG: error during NLMSG_PUT\n");

alloc_failure:
	PRINTR("ipt_ULOG: Error building netlink message\n");

	spin_unlock_bh(&ulog_lock);
}