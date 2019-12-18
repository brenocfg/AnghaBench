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
struct xfrm_audit {scalar_t__ secid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; int /*<<< orphan*/  sadb_msg_satype; } ;
struct net {int dummy; } ;
struct TYPE_2__ {unsigned int proto; } ;
struct km_event {struct net* net; int /*<<< orphan*/  event; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; TYPE_1__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  XFRM_MSG_FLUSHSA ; 
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  km_state_notify (int /*<<< orphan*/ *,struct km_event*) ; 
 unsigned int pfkey_satype2proto (int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int unicast_flush_resp (struct sock*,struct sadb_msg*) ; 
 int xfrm_state_flush (struct net*,unsigned int,struct xfrm_audit*) ; 

__attribute__((used)) static int pfkey_flush(struct sock *sk, struct sk_buff *skb, struct sadb_msg *hdr, void **ext_hdrs)
{
	struct net *net = sock_net(sk);
	unsigned proto;
	struct km_event c;
	struct xfrm_audit audit_info;
	int err, err2;

	proto = pfkey_satype2proto(hdr->sadb_msg_satype);
	if (proto == 0)
		return -EINVAL;

	audit_info.loginuid = audit_get_loginuid(current);
	audit_info.sessionid = audit_get_sessionid(current);
	audit_info.secid = 0;
	err = xfrm_state_flush(net, proto, &audit_info);
	err2 = unicast_flush_resp(sk, hdr);
	if (err || err2) {
		if (err == -ESRCH) /* empty table - go quietly */
			err = 0;
		return err ? err : err2;
	}

	c.data.proto = proto;
	c.seq = hdr->sadb_msg_seq;
	c.pid = hdr->sadb_msg_pid;
	c.event = XFRM_MSG_FLUSHSA;
	c.net = net;
	km_state_notify(NULL, &c);

	return 0;
}