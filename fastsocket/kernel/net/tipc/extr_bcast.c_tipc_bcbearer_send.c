#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct tipc_msg {int dummy; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_bearer {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_21__ {scalar_t__ blocked; } ;
struct bearer {TYPE_1__* media; TYPE_9__ publ; int /*<<< orphan*/  nodes; } ;
struct TYPE_20__ {scalar_t__ count; } ;
struct TYPE_19__ {int /*<<< orphan*/  bearer_congs; } ;
struct TYPE_17__ {int blocked; } ;
struct TYPE_18__ {TYPE_3__ publ; } ;
struct TYPE_16__ {struct bearer* secondary; struct bearer* primary; } ;
struct TYPE_15__ {int /*<<< orphan*/  bcast_addr; scalar_t__ (* send_msg ) (struct sk_buff*,TYPE_9__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_4__ bearer; TYPE_6__ remains_new; TYPE_6__ remains; TYPE_2__* bpairs; } ;
struct TYPE_13__ {TYPE_5__ stats; } ;

/* Variables and functions */
 int MAX_BEARERS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_12__* bcbearer ; 
 int /*<<< orphan*/  bcbuf_set_acks (struct sk_buff*,scalar_t__) ; 
 TYPE_11__* bcl ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_non_seq (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_mc_netid (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_non_seq (struct tipc_msg*,int) ; 
 scalar_t__ stub1 (struct sk_buff*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct sk_buff*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_6__ tipc_cltr_bcast_nodes ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tipc_nmap_diff (TYPE_6__*,int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static int tipc_bcbearer_send(struct sk_buff *buf,
			      struct tipc_bearer *unused1,
			      struct tipc_media_addr *unused2)
{
	static int send_count = 0;

	int bp_index;
	int swap_time;

	/* Prepare buffer for broadcasting (if first time trying to send it) */

	if (likely(!msg_non_seq(buf_msg(buf)))) {
		struct tipc_msg *msg;

		assert(tipc_cltr_bcast_nodes.count != 0);
		bcbuf_set_acks(buf, tipc_cltr_bcast_nodes.count);
		msg = buf_msg(buf);
		msg_set_non_seq(msg, 1);
		msg_set_mc_netid(msg, tipc_net_id);
	}

	/* Determine if bearer pairs should be swapped following this attempt */

	if ((swap_time = (++send_count >= 10)))
		send_count = 0;

	/* Send buffer over bearers until all targets reached */

	bcbearer->remains = tipc_cltr_bcast_nodes;

	for (bp_index = 0; bp_index < MAX_BEARERS; bp_index++) {
		struct bearer *p = bcbearer->bpairs[bp_index].primary;
		struct bearer *s = bcbearer->bpairs[bp_index].secondary;

		if (!p)
			break;	/* no more bearers to try */

		tipc_nmap_diff(&bcbearer->remains, &p->nodes, &bcbearer->remains_new);
		if (bcbearer->remains_new.count == bcbearer->remains.count)
			continue;	/* bearer pair doesn't add anything */

		if (!p->publ.blocked &&
		    !p->media->send_msg(buf, &p->publ, &p->media->bcast_addr)) {
			if (swap_time && s && !s->publ.blocked)
				goto swap;
			else
				goto update;
		}

		if (!s || s->publ.blocked ||
		    s->media->send_msg(buf, &s->publ, &s->media->bcast_addr))
			continue;	/* unable to send using bearer pair */
swap:
		bcbearer->bpairs[bp_index].primary = s;
		bcbearer->bpairs[bp_index].secondary = p;
update:
		if (bcbearer->remains_new.count == 0)
			return 0;

		bcbearer->remains = bcbearer->remains_new;
	}

	/* Unable to reach all targets */

	bcbearer->bearer.publ.blocked = 1;
	bcl->stats.bearer_congs++;
	return 1;
}