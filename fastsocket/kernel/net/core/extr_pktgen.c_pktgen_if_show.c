#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct seq_file {struct pktgen_dev* private; } ;
struct TYPE_11__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s6_addr; } ;
struct pktgen_dev {int cflows; int flags; unsigned int nr_labels; int vlan_id; int svlan_id; int tos; int traffic_class; scalar_t__* result; int /*<<< orphan*/  nflows; int /*<<< orphan*/  cur_queue_map; int /*<<< orphan*/  cur_udp_src; int /*<<< orphan*/  cur_udp_dst; int /*<<< orphan*/  cur_daddr; int /*<<< orphan*/  cur_saddr; TYPE_2__ cur_in6_saddr; TYPE_1__ cur_in6_daddr; int /*<<< orphan*/  cur_src_mac_offset; int /*<<< orphan*/  cur_dst_mac_offset; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  started_at; scalar_t__ errors; scalar_t__ sofar; scalar_t__ idle_acc; int /*<<< orphan*/  stopped_at; scalar_t__ running; int /*<<< orphan*/  svlan_cfi; int /*<<< orphan*/  svlan_p; int /*<<< orphan*/  vlan_cfi; int /*<<< orphan*/  vlan_p; int /*<<< orphan*/ * labels; int /*<<< orphan*/  dst_mac_count; int /*<<< orphan*/  src_mac_count; int /*<<< orphan*/  udp_dst_max; int /*<<< orphan*/  udp_dst_min; int /*<<< orphan*/  udp_src_max; int /*<<< orphan*/  udp_src_min; int /*<<< orphan*/  dst_mac; int /*<<< orphan*/  src_mac; TYPE_9__* odev; int /*<<< orphan*/  src_max; int /*<<< orphan*/  src_min; int /*<<< orphan*/  dst_max; int /*<<< orphan*/  dst_min; TYPE_8__ max_in6_daddr; TYPE_7__ min_in6_daddr; TYPE_6__ in6_daddr; TYPE_5__ max_in6_saddr; TYPE_4__ min_in6_saddr; TYPE_3__ in6_saddr; int /*<<< orphan*/  queue_map_max; int /*<<< orphan*/  queue_map_min; int /*<<< orphan*/  lflow; int /*<<< orphan*/  odevname; int /*<<< orphan*/  clone_skb; scalar_t__ delay; int /*<<< orphan*/  nfrags; int /*<<< orphan*/  max_pkt_size; int /*<<< orphan*/  min_pkt_size; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_18__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int F_FLOW_SEQ ; 
 int F_IPDST_RND ; 
 int F_IPSEC_ON ; 
 int F_IPSRC_RND ; 
 int F_IPV6 ; 
 int F_MACDST_RND ; 
 int F_MACSRC_RND ; 
 int F_MPLS_RND ; 
 int F_QUEUE_MAP_CPU ; 
 int F_QUEUE_MAP_RND ; 
 int F_SVID_RND ; 
 int F_TXSIZE_RND ; 
 int F_UDPDST_RND ; 
 int F_UDPSRC_RND ; 
 int F_VID_RND ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt_ip6 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_now () ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int pktgen_if_show(struct seq_file *seq, void *v)
{
	const struct pktgen_dev *pkt_dev = seq->private;
	ktime_t stopped;
	u64 idle;

	seq_printf(seq,
		   "Params: count %llu  min_pkt_size: %u  max_pkt_size: %u\n",
		   (unsigned long long)pkt_dev->count, pkt_dev->min_pkt_size,
		   pkt_dev->max_pkt_size);

	seq_printf(seq,
		   "     frags: %d  delay: %llu  clone_skb: %d  ifname: %s\n",
		   pkt_dev->nfrags, (unsigned long long) pkt_dev->delay,
		   pkt_dev->clone_skb, pkt_dev->odevname);

	seq_printf(seq, "     flows: %u flowlen: %u\n", pkt_dev->cflows,
		   pkt_dev->lflow);

	seq_printf(seq,
		   "     queue_map_min: %u  queue_map_max: %u\n",
		   pkt_dev->queue_map_min,
		   pkt_dev->queue_map_max);

	if (pkt_dev->flags & F_IPV6) {
		char b1[128], b2[128], b3[128];
		fmt_ip6(b1, pkt_dev->in6_saddr.s6_addr);
		fmt_ip6(b2, pkt_dev->min_in6_saddr.s6_addr);
		fmt_ip6(b3, pkt_dev->max_in6_saddr.s6_addr);
		seq_printf(seq,
			   "     saddr: %s  min_saddr: %s  max_saddr: %s\n", b1,
			   b2, b3);

		fmt_ip6(b1, pkt_dev->in6_daddr.s6_addr);
		fmt_ip6(b2, pkt_dev->min_in6_daddr.s6_addr);
		fmt_ip6(b3, pkt_dev->max_in6_daddr.s6_addr);
		seq_printf(seq,
			   "     daddr: %s  min_daddr: %s  max_daddr: %s\n", b1,
			   b2, b3);

	} else {
		seq_printf(seq,
			   "     dst_min: %s  dst_max: %s\n",
			   pkt_dev->dst_min, pkt_dev->dst_max);
		seq_printf(seq,
			   "        src_min: %s  src_max: %s\n",
			   pkt_dev->src_min, pkt_dev->src_max);
	}

	seq_puts(seq, "     src_mac: ");

	seq_printf(seq, "%pM ",
		   is_zero_ether_addr(pkt_dev->src_mac) ?
			     pkt_dev->odev->dev_addr : pkt_dev->src_mac);

	seq_printf(seq, "dst_mac: ");
	seq_printf(seq, "%pM\n", pkt_dev->dst_mac);

	seq_printf(seq,
		   "     udp_src_min: %d  udp_src_max: %d"
		   "  udp_dst_min: %d  udp_dst_max: %d\n",
		   pkt_dev->udp_src_min, pkt_dev->udp_src_max,
		   pkt_dev->udp_dst_min, pkt_dev->udp_dst_max);

	seq_printf(seq,
		   "     src_mac_count: %d  dst_mac_count: %d\n",
		   pkt_dev->src_mac_count, pkt_dev->dst_mac_count);

	if (pkt_dev->nr_labels) {
		unsigned i;
		seq_printf(seq, "     mpls: ");
		for (i = 0; i < pkt_dev->nr_labels; i++)
			seq_printf(seq, "%08x%s", ntohl(pkt_dev->labels[i]),
				   i == pkt_dev->nr_labels-1 ? "\n" : ", ");
	}

	if (pkt_dev->vlan_id != 0xffff)
		seq_printf(seq, "     vlan_id: %u  vlan_p: %u  vlan_cfi: %u\n",
			   pkt_dev->vlan_id, pkt_dev->vlan_p,
			   pkt_dev->vlan_cfi);

	if (pkt_dev->svlan_id != 0xffff)
		seq_printf(seq, "     svlan_id: %u  vlan_p: %u  vlan_cfi: %u\n",
			   pkt_dev->svlan_id, pkt_dev->svlan_p,
			   pkt_dev->svlan_cfi);

	if (pkt_dev->tos)
		seq_printf(seq, "     tos: 0x%02x\n", pkt_dev->tos);

	if (pkt_dev->traffic_class)
		seq_printf(seq, "     traffic_class: 0x%02x\n", pkt_dev->traffic_class);

	seq_printf(seq, "     Flags: ");

	if (pkt_dev->flags & F_IPV6)
		seq_printf(seq, "IPV6  ");

	if (pkt_dev->flags & F_IPSRC_RND)
		seq_printf(seq, "IPSRC_RND  ");

	if (pkt_dev->flags & F_IPDST_RND)
		seq_printf(seq, "IPDST_RND  ");

	if (pkt_dev->flags & F_TXSIZE_RND)
		seq_printf(seq, "TXSIZE_RND  ");

	if (pkt_dev->flags & F_UDPSRC_RND)
		seq_printf(seq, "UDPSRC_RND  ");

	if (pkt_dev->flags & F_UDPDST_RND)
		seq_printf(seq, "UDPDST_RND  ");

	if (pkt_dev->flags & F_MPLS_RND)
		seq_printf(seq,  "MPLS_RND  ");

	if (pkt_dev->flags & F_QUEUE_MAP_RND)
		seq_printf(seq,  "QUEUE_MAP_RND  ");

	if (pkt_dev->flags & F_QUEUE_MAP_CPU)
		seq_printf(seq,  "QUEUE_MAP_CPU  ");

	if (pkt_dev->cflows) {
		if (pkt_dev->flags & F_FLOW_SEQ)
			seq_printf(seq,  "FLOW_SEQ  "); /*in sequence flows*/
		else
			seq_printf(seq,  "FLOW_RND  ");
	}

#ifdef CONFIG_XFRM
	if (pkt_dev->flags & F_IPSEC_ON)
		seq_printf(seq,  "IPSEC  ");
#endif

	if (pkt_dev->flags & F_MACSRC_RND)
		seq_printf(seq, "MACSRC_RND  ");

	if (pkt_dev->flags & F_MACDST_RND)
		seq_printf(seq, "MACDST_RND  ");

	if (pkt_dev->flags & F_VID_RND)
		seq_printf(seq, "VID_RND  ");

	if (pkt_dev->flags & F_SVID_RND)
		seq_printf(seq, "SVID_RND  ");

	seq_puts(seq, "\n");

	/* not really stopped, more like last-running-at */
	stopped = pkt_dev->running ? ktime_now() : pkt_dev->stopped_at;
	idle = pkt_dev->idle_acc;
	do_div(idle, NSEC_PER_USEC);

	seq_printf(seq,
		   "Current:\n     pkts-sofar: %llu  errors: %llu\n",
		   (unsigned long long)pkt_dev->sofar,
		   (unsigned long long)pkt_dev->errors);

	seq_printf(seq,
		   "     started: %lluus  stopped: %lluus idle: %lluus\n",
		   (unsigned long long) ktime_to_us(pkt_dev->started_at),
		   (unsigned long long) ktime_to_us(stopped),
		   (unsigned long long) idle);

	seq_printf(seq,
		   "     seq_num: %d  cur_dst_mac_offset: %d  cur_src_mac_offset: %d\n",
		   pkt_dev->seq_num, pkt_dev->cur_dst_mac_offset,
		   pkt_dev->cur_src_mac_offset);

	if (pkt_dev->flags & F_IPV6) {
		char b1[128], b2[128];
		fmt_ip6(b1, pkt_dev->cur_in6_daddr.s6_addr);
		fmt_ip6(b2, pkt_dev->cur_in6_saddr.s6_addr);
		seq_printf(seq, "     cur_saddr: %s  cur_daddr: %s\n", b2, b1);
	} else
		seq_printf(seq, "     cur_saddr: 0x%x  cur_daddr: 0x%x\n",
			   pkt_dev->cur_saddr, pkt_dev->cur_daddr);

	seq_printf(seq, "     cur_udp_dst: %d  cur_udp_src: %d\n",
		   pkt_dev->cur_udp_dst, pkt_dev->cur_udp_src);

	seq_printf(seq, "     cur_queue_map: %u\n", pkt_dev->cur_queue_map);

	seq_printf(seq, "     flows: %u\n", pkt_dev->nflows);

	if (pkt_dev->result[0])
		seq_printf(seq, "Result: %s\n", pkt_dev->result);
	else
		seq_printf(seq, "Result: Idle\n");

	return 0;
}