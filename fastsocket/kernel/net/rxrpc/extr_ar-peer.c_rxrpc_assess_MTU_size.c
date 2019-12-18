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
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {TYPE_1__ sin_addr; } ;
struct TYPE_12__ {int family; TYPE_2__ sin; } ;
struct TYPE_13__ {TYPE_3__ transport; } ;
struct rxrpc_peer {int if_mtu; TYPE_4__ srx; } ;
struct TYPE_18__ {int /*<<< orphan*/  dst; } ;
struct rtable {TYPE_9__ u; } ;
struct TYPE_16__ {void* dport; void* sport; } ;
struct TYPE_17__ {TYPE_7__ ports; } ;
struct TYPE_14__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_15__ {TYPE_5__ ip4_u; } ;
struct flowi {TYPE_8__ uli_u; TYPE_6__ nl_u; int /*<<< orphan*/  proto; int /*<<< orphan*/  oif; } ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int dst_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  init_net ; 
 int ip_route_output_key (int /*<<< orphan*/ *,struct rtable**,struct flowi*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rxrpc_assess_MTU_size(struct rxrpc_peer *peer)
{
	struct rtable *rt;
	struct flowi fl;
	int ret;

	peer->if_mtu = 1500;

	memset(&fl, 0, sizeof(fl));

	switch (peer->srx.transport.family) {
	case AF_INET:
		fl.oif = 0;
		fl.proto = IPPROTO_UDP,
		fl.nl_u.ip4_u.saddr = 0;
		fl.nl_u.ip4_u.daddr = peer->srx.transport.sin.sin_addr.s_addr;
		fl.nl_u.ip4_u.tos = 0;
		/* assume AFS.CM talking to AFS.FS */
		fl.uli_u.ports.sport = htons(7001);
		fl.uli_u.ports.dport = htons(7000);
		break;
	default:
		BUG();
	}

	ret = ip_route_output_key(&init_net, &rt, &fl);
	if (ret < 0) {
		_leave(" [route err %d]", ret);
		return;
	}

	peer->if_mtu = dst_mtu(&rt->u.dst);
	dst_release(&rt->u.dst);

	_leave(" [if_mtu %u]", peer->if_mtu);
}