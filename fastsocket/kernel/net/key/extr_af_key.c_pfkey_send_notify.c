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
struct xfrm_state {int dummy; } ;
struct netns_pfkey {int /*<<< orphan*/  socks_nr; } ;
struct net {int dummy; } ;
struct km_event {int event; struct net* net; } ;

/* Variables and functions */
#define  XFRM_MSG_DELSA 133 
#define  XFRM_MSG_EXPIRE 132 
#define  XFRM_MSG_FLUSHSA 131 
#define  XFRM_MSG_NEWAE 130 
#define  XFRM_MSG_NEWSA 129 
#define  XFRM_MSG_UPDSA 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int key_notify_sa (struct xfrm_state*,struct km_event*) ; 
 int key_notify_sa_expire (struct xfrm_state*,struct km_event*) ; 
 int key_notify_sa_flush (struct km_event*) ; 
 struct netns_pfkey* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_net_id ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int pfkey_send_notify(struct xfrm_state *x, struct km_event *c)
{
	struct net *net = x ? xs_net(x) : c->net;
	struct netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	if (atomic_read(&net_pfkey->socks_nr) == 0)
		return 0;

	switch (c->event) {
	case XFRM_MSG_EXPIRE:
		return key_notify_sa_expire(x, c);
	case XFRM_MSG_DELSA:
	case XFRM_MSG_NEWSA:
	case XFRM_MSG_UPDSA:
		return key_notify_sa(x, c);
	case XFRM_MSG_FLUSHSA:
		return key_notify_sa_flush(c);
	case XFRM_MSG_NEWAE: /* not yet supported */
		break;
	default:
		printk("pfkey: Unknown SA event %d\n", c->event);
		break;
	}

	return 0;
}