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
struct udphdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ family; } ;
struct sockaddr_rxrpc {int transport_type; TYPE_1__ transport; } ;
struct rxrpc_peer {int hdrsize; scalar_t__ mtu; scalar_t__ maxdata; scalar_t__ if_mtu; int /*<<< orphan*/  srx; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  usage; int /*<<< orphan*/  lock; int /*<<< orphan*/  error_targets; int /*<<< orphan*/  link; int /*<<< orphan*/  destroyer; } ;
struct rxrpc_header {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  SOCK_DGRAM 128 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_peer*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rxrpc_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_rxrpc*,int) ; 
 int /*<<< orphan*/  rxrpc_assess_MTU_size (struct rxrpc_peer*) ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_destroy_peer ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rxrpc_peer *rxrpc_alloc_peer(struct sockaddr_rxrpc *srx,
					   gfp_t gfp)
{
	struct rxrpc_peer *peer;

	_enter("");

	peer = kzalloc(sizeof(struct rxrpc_peer), gfp);
	if (peer) {
		INIT_WORK(&peer->destroyer, &rxrpc_destroy_peer);
		INIT_LIST_HEAD(&peer->link);
		INIT_LIST_HEAD(&peer->error_targets);
		spin_lock_init(&peer->lock);
		atomic_set(&peer->usage, 1);
		peer->debug_id = atomic_inc_return(&rxrpc_debug_id);
		memcpy(&peer->srx, srx, sizeof(*srx));

		rxrpc_assess_MTU_size(peer);
		peer->mtu = peer->if_mtu;

		if (srx->transport.family == AF_INET) {
			peer->hdrsize = sizeof(struct iphdr);
			switch (srx->transport_type) {
			case SOCK_DGRAM:
				peer->hdrsize += sizeof(struct udphdr);
				break;
			default:
				BUG();
				break;
			}
		} else {
			BUG();
		}

		peer->hdrsize += sizeof(struct rxrpc_header);
		peer->maxdata = peer->mtu - peer->hdrsize;
	}

	_leave(" = %p", peer);
	return peer;
}