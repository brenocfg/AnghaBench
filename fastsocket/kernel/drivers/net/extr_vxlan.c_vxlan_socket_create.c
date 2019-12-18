#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vxlan_rcv_t ;
typedef  int /*<<< orphan*/  vxlan_addr ;
struct vxlan_sock {int /*<<< orphan*/  hlist; void* data; int /*<<< orphan*/ * rcv; int /*<<< orphan*/  refcnt; TYPE_3__* sock; int /*<<< orphan*/  del_work; int /*<<< orphan*/ * vni_list; } ;
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_9__ {scalar_t__ mc_loop; } ;
struct TYPE_8__ {struct sock* sk; } ;
struct TYPE_7__ {int encap_type; int /*<<< orphan*/  encap_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOMEM ; 
 struct vxlan_sock* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 unsigned int VNI_HASH_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_5__* inet_sk (struct sock*) ; 
 int kernel_bind (TYPE_3__*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  kfree (struct vxlan_sock*) ; 
 struct vxlan_sock* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct vxlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sk_change_net (struct sock*,struct net*) ; 
 int /*<<< orphan*/  sk_release_kernel (struct sock*) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  vs_head (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_del_work ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 int /*<<< orphan*/  vxlan_udp_encap_recv ; 

__attribute__((used)) static struct vxlan_sock *vxlan_socket_create(struct net *net, __be16 port,
					      vxlan_rcv_t *rcv, void *data)
{
	struct vxlan_net *vn = net_generic(net, vxlan_net_id);
	struct vxlan_sock *vs;
	struct sock *sk;
	struct sockaddr_in vxlan_addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_ANY),
		.sin_port = port,
	};
	int rc;
	unsigned int h;

	vs = kmalloc(sizeof(*vs), GFP_KERNEL);
	if (!vs) {
		pr_debug("memory alocation failure\n");
		return ERR_PTR(-ENOMEM);
	}

	for (h = 0; h < VNI_HASH_SIZE; ++h)
		INIT_HLIST_HEAD(&vs->vni_list[h]);

	INIT_WORK(&vs->del_work, vxlan_del_work);

	/* Create UDP socket for encapsulation receive. */
	rc = sock_create_kern(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &vs->sock);
	if (rc < 0) {
		pr_debug("UDP socket create failed\n");
		kfree(vs);
		return ERR_PTR(rc);
	}

	/* Put in proper namespace */
	sk = vs->sock->sk;
	sk_change_net(sk, net);

	rc = kernel_bind(vs->sock, (struct sockaddr *) &vxlan_addr,
			 sizeof(vxlan_addr));
	if (rc < 0) {
		pr_debug("bind for UDP socket %pI4:%u (%d)\n",
			 &vxlan_addr.sin_addr, ntohs(vxlan_addr.sin_port), rc);
		sk_release_kernel(sk);
		kfree(vs);
		return ERR_PTR(rc);
	}
	atomic_set(&vs->refcnt, 1);
	vs->rcv = rcv;
	vs->data = data;

	/* Disable multicast loopback */
	inet_sk(sk)->mc_loop = 0;
	spin_lock(&vn->sock_lock);
	hlist_add_head_rcu(&vs->hlist, vs_head(net, port));
	spin_unlock(&vn->sock_lock);

	/* Mark socket as an encapsulation socket. */
	udp_sk(sk)->encap_type = 1;
	udp_sk(sk)->encap_rcv = vxlan_udp_encap_recv;
	return vs;
}