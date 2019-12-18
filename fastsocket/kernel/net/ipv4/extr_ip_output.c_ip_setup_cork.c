#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; TYPE_1__* dev; } ;
struct TYPE_6__ {TYPE_2__ dst; } ;
struct rtable {TYPE_3__ u; } ;
struct ipcm_cookie {int /*<<< orphan*/  addr; struct ip_options* opt; } ;
struct ip_options {scalar_t__ optlen; } ;
struct inet_sock {scalar_t__ pmtudisc; } ;
struct inet_cork {scalar_t__ length; TYPE_2__* dst; int /*<<< orphan*/  fragsize; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; int /*<<< orphan*/ * opt; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IPCORK_OPT ; 
 scalar_t__ IP_PMTUDISC_PROBE ; 
 int /*<<< orphan*/  dst_mtu (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ip_options*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_setup_cork(struct sock *sk, struct inet_cork *cork,
			 struct ipcm_cookie *ipc, struct rtable **rtp)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ip_options *opt;
	struct rtable *rt;

	/*
	 * setup for corking.
	 */
	opt = ipc->opt;
	if (opt) {
		if (cork->opt == NULL) {
			cork->opt = kmalloc(sizeof(struct ip_options) + 40,
					    sk->sk_allocation);
			if (unlikely(cork->opt == NULL))
				return -ENOBUFS;
		}
		memcpy(cork->opt, opt, sizeof(struct ip_options) + opt->optlen);
		cork->flags |= IPCORK_OPT;
		cork->addr = ipc->addr;
	}
	rt = *rtp;
	if (unlikely(!rt))
		return -EFAULT;
	/*
	 * We steal reference to this route, caller should not release it
	 */
	*rtp = NULL;
	cork->fragsize = inet->pmtudisc == IP_PMTUDISC_PROBE ?
			 rt->u.dst.dev->mtu : dst_mtu(rt->u.dst.path);
	cork->dst = &rt->u.dst;
	cork->length = 0;

	return 0;
}