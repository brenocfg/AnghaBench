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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct phonet_net {TYPE_1__ pndevs; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct phonet_net*) ; 
 struct phonet_net* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_assign_generic (struct net*,int /*<<< orphan*/ ,struct phonet_net*) ; 
 int /*<<< orphan*/  phonet_net_id ; 
 int /*<<< orphan*/  pn_sock_seq_fops ; 
 int /*<<< orphan*/  proc_net_fops_create (struct net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phonet_init_net(struct net *net)
{
	struct phonet_net *pnn = kmalloc(sizeof(*pnn), GFP_KERNEL);
	if (!pnn)
		return -ENOMEM;

	if (!proc_net_fops_create(net, "phonet", 0, &pn_sock_seq_fops)) {
		kfree(pnn);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&pnn->pndevs.list);
	spin_lock_init(&pnn->pndevs.lock);
	net_assign_generic(net, phonet_net_id, pnn);
	return 0;
}