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
typedef  int uint8_t ;
typedef  unsigned short uint16_t ;
struct sk_buff {unsigned int len; int network_header; int mac_header; } ;
struct net_device {int dummy; } ;
struct arcnet_local {int* default_proto; } ;
struct ArcProto {int suffix; int (* build_header ) (struct sk_buff*,struct net_device*,unsigned short,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  D_DEBUG ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_NORMAL ; 
 unsigned short ETH_P_ARCNET ; 
 struct ArcProto* arc_bcast_proto ; 
 struct ArcProto** arc_proto_map ; 
 struct ArcProto arc_proto_null ; 
 struct ArcProto* arc_raw_proto ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int stub1 (struct sk_buff*,struct net_device*,unsigned short,int) ; 

__attribute__((used)) static int arcnet_header(struct sk_buff *skb, struct net_device *dev,
			 unsigned short type, const void *daddr,
			 const void *saddr, unsigned len)
{
	const struct arcnet_local *lp = netdev_priv(dev);
	uint8_t _daddr, proto_num;
	struct ArcProto *proto;

	BUGMSG(D_DURING,
	    "create header from %d to %d; protocol %d (%Xh); size %u.\n",
	       saddr ? *(uint8_t *) saddr : -1,
	       daddr ? *(uint8_t *) daddr : -1,
	       type, type, len);

	if (skb->len!=0 && len != skb->len)
		BUGMSG(D_NORMAL, "arcnet_header: Yikes!  skb->len(%d) != len(%d)!\n",
		       skb->len, len);


  	/* Type is host order - ? */
  	if(type == ETH_P_ARCNET) {
  		proto = arc_raw_proto;
  		BUGMSG(D_DEBUG, "arc_raw_proto used. proto='%c'\n",proto->suffix);
  		_daddr = daddr ? *(uint8_t *) daddr : 0;
  	}
	else if (!daddr) {
		/*
		 * if the dest addr isn't provided, we can't choose an encapsulation!
		 * Store the packet type (eg. ETH_P_IP) for now, and we'll push on a
		 * real header when we do rebuild_header.
		 */
		*(uint16_t *) skb_push(skb, 2) = type;
		/*
		 * XXX: Why not use skb->mac_len?
		 */
		if (skb->network_header - skb->mac_header != 2)
			BUGMSG(D_NORMAL, "arcnet_header: Yikes!  diff (%d) is not 2!\n",
			       (int)(skb->network_header - skb->mac_header));
		return -2;	/* return error -- can't transmit yet! */
	}
	else {
		/* otherwise, we can just add the header as usual. */
		_daddr = *(uint8_t *) daddr;
		proto_num = lp->default_proto[_daddr];
		proto = arc_proto_map[proto_num];
		BUGMSG(D_DURING, "building header for %02Xh using protocol '%c'\n",
		       proto_num, proto->suffix);
		if (proto == &arc_proto_null && arc_bcast_proto != proto) {
			BUGMSG(D_DURING, "actually, let's use '%c' instead.\n",
			       arc_bcast_proto->suffix);
			proto = arc_bcast_proto;
		}
	}
	return proto->build_header(skb, dev, type, _daddr);
}