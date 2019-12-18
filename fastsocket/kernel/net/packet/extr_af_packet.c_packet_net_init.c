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
struct TYPE_2__ {int /*<<< orphan*/  sklist; int /*<<< orphan*/  sklist_lock; } ;
struct net {TYPE_1__ packet; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_seq_fops ; 
 int /*<<< orphan*/  proc_net_fops_create (struct net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int packet_net_init(struct net *net)
{
	rwlock_init(&net->packet.sklist_lock);
	INIT_HLIST_HEAD(&net->packet.sklist);

	if (!proc_net_fops_create(net, "packet", 0, &packet_seq_fops))
		return -ENOMEM;

	return 0;
}