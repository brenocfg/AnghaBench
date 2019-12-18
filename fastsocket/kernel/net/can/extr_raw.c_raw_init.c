#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_3__ {int /*<<< orphan*/  can_mask; scalar_t__ can_id; } ;
struct raw_sock {int count; int loopback; TYPE_2__ notifier; scalar_t__ recv_own_msgs; TYPE_1__ dfilter; TYPE_1__* filter; scalar_t__ ifindex; scalar_t__ bound; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_ALL ; 
 int /*<<< orphan*/  raw_notifier ; 
 struct raw_sock* raw_sk (struct sock*) ; 
 int /*<<< orphan*/  register_netdevice_notifier (TYPE_2__*) ; 

__attribute__((used)) static int raw_init(struct sock *sk)
{
	struct raw_sock *ro = raw_sk(sk);

	ro->bound            = 0;
	ro->ifindex          = 0;

	/* set default filter to single entry dfilter */
	ro->dfilter.can_id   = 0;
	ro->dfilter.can_mask = MASK_ALL;
	ro->filter           = &ro->dfilter;
	ro->count            = 1;

	/* set default loopback behaviour */
	ro->loopback         = 1;
	ro->recv_own_msgs    = 0;

	/* set notifier */
	ro->notifier.notifier_call = raw_notifier;

	register_netdevice_notifier(&ro->notifier);

	return 0;
}