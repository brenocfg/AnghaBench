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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_len; int /*<<< orphan*/  nlmsg_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {TYPE_1__ get_stats; } ;
struct iscsi_uevent {int custom_length; TYPE_2__ u; int /*<<< orphan*/  type; int /*<<< orphan*/  transport_handle; } ;
struct iscsi_transport {int /*<<< orphan*/  (* get_stats ) (struct iscsi_cls_conn*,struct iscsi_uevent*) ;} ;
struct iscsi_stats_custom {int dummy; } ;
struct iscsi_stats {int custom_length; TYPE_2__ u; int /*<<< orphan*/  type; int /*<<< orphan*/  transport_handle; } ;
struct iscsi_internal {int dummy; } ;
struct iscsi_cls_conn {int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ISCSI_NL_GRP_ISCSID ; 
 int ISCSI_STATS_CUSTOM_MAX ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NLMSG_ALIGN (int) ; 
 struct iscsi_uevent* NLMSG_DATA (struct nlmsghdr*) ; 
 int NLMSG_LENGTH (int) ; 
 int NLMSG_SPACE (int) ; 
 struct nlmsghdr* __nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_cls_conn_printk (int /*<<< orphan*/ ,struct iscsi_cls_conn*,char*) ; 
 struct iscsi_cls_conn* iscsi_conn_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_handle (int /*<<< orphan*/ ) ; 
 struct iscsi_internal* iscsi_if_transport_lookup (struct iscsi_transport*) ; 
 int iscsi_multicast_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iscsi_uevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_cls_conn*,struct iscsi_uevent*) ; 

__attribute__((used)) static int
iscsi_if_get_stats(struct iscsi_transport *transport, struct nlmsghdr *nlh)
{
	struct iscsi_uevent *ev = NLMSG_DATA(nlh);
	struct iscsi_stats *stats;
	struct sk_buff *skbstat;
	struct iscsi_cls_conn *conn;
	struct nlmsghdr	*nlhstat;
	struct iscsi_uevent *evstat;
	struct iscsi_internal *priv;
	int len = NLMSG_SPACE(sizeof(*ev) +
			      sizeof(struct iscsi_stats) +
			      sizeof(struct iscsi_stats_custom) *
			      ISCSI_STATS_CUSTOM_MAX);
	int err = 0;

	priv = iscsi_if_transport_lookup(transport);
	if (!priv)
		return -EINVAL;

	conn = iscsi_conn_lookup(ev->u.get_stats.sid, ev->u.get_stats.cid);
	if (!conn)
		return -EEXIST;

	do {
		int actual_size;

		skbstat = alloc_skb(len, GFP_ATOMIC);
		if (!skbstat) {
			iscsi_cls_conn_printk(KERN_ERR, conn, "can not "
					      "deliver stats: OOM\n");
			return -ENOMEM;
		}

		nlhstat = __nlmsg_put(skbstat, 0, 0, 0,
				      (len - sizeof(*nlhstat)), 0);
		evstat = NLMSG_DATA(nlhstat);
		memset(evstat, 0, sizeof(*evstat));
		evstat->transport_handle = iscsi_handle(conn->transport);
		evstat->type = nlh->nlmsg_type;
		evstat->u.get_stats.cid =
			ev->u.get_stats.cid;
		evstat->u.get_stats.sid =
			ev->u.get_stats.sid;
		stats = (struct iscsi_stats *)
			((char*)evstat + sizeof(*evstat));
		memset(stats, 0, sizeof(*stats));

		transport->get_stats(conn, stats);
		actual_size = NLMSG_SPACE(sizeof(struct iscsi_uevent) +
					  sizeof(struct iscsi_stats) +
					  sizeof(struct iscsi_stats_custom) *
					  stats->custom_length);
		actual_size -= sizeof(*nlhstat);
		actual_size = NLMSG_LENGTH(actual_size);
		skb_trim(skbstat, NLMSG_ALIGN(actual_size));
		nlhstat->nlmsg_len = actual_size;

		err = iscsi_multicast_skb(skbstat, ISCSI_NL_GRP_ISCSID,
					  GFP_ATOMIC);
	} while (err < 0 && err != -ECONNREFUSED);

	return err;
}