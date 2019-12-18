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
struct netns_proto_gre {int /*<<< orphan*/  keymap_list; int /*<<< orphan*/  keymap_lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct netns_proto_gre*) ; 
 struct netns_proto_gre* kmalloc (int,int /*<<< orphan*/ ) ; 
 int net_assign_generic (struct net*,int /*<<< orphan*/ ,struct netns_proto_gre*) ; 
 int /*<<< orphan*/  proto_gre_net_id ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proto_gre_net_init(struct net *net)
{
	struct netns_proto_gre *net_gre;
	int rv;

	net_gre = kmalloc(sizeof(struct netns_proto_gre), GFP_KERNEL);
	if (!net_gre)
		return -ENOMEM;
	rwlock_init(&net_gre->keymap_lock);
	INIT_LIST_HEAD(&net_gre->keymap_list);

	rv = net_assign_generic(net, proto_gre_net_id, net_gre);
	if (rv < 0)
		kfree(net_gre);
	return rv;
}