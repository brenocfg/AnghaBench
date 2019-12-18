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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_SECURITY ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  security_release_secctx (char*,int /*<<< orphan*/ ) ; 
 int security_secid_to_secctx (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int security_socket_getpeersec_dgram (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip_cmsg_recv_security(struct msghdr *msg, struct sk_buff *skb)
{
	char *secdata;
	u32 seclen, secid;
	int err;

	err = security_socket_getpeersec_dgram(NULL, skb, &secid);
	if (err)
		return;

	err = security_secid_to_secctx(secid, &secdata, &seclen);
	if (err)
		return;

	put_cmsg(msg, SOL_IP, SCM_SECURITY, seclen, secdata);
	security_release_secctx(secdata, seclen);
}