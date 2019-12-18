#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {TYPE_4__* in_ops; int /*<<< orphan*/  ingress_lock; TYPE_3__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_dst_ip; } ;
struct TYPE_6__ {TYPE_1__ in_info; } ;
struct k_message {int /*<<< orphan*/  ip_mask; TYPE_2__ content; } ;
typedef  int /*<<< orphan*/  in_cache_entry ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int /*<<< orphan*/ * (* get_with_mask ) (int /*<<< orphan*/ ,struct mpoa_client*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* remove_entry ) (int /*<<< orphan*/ *,struct mpoa_client*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,struct mpoa_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ ,struct mpoa_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ingress_purge_rcvd(struct k_message *msg, struct mpoa_client *mpc)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	__be32 mask = msg->ip_mask;
	in_cache_entry *entry = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);

	if(entry == NULL){
		printk("mpoa: (%s) ingress_purge_rcvd: purge for a non-existing entry, ip = %pI4\n",
		       mpc->dev->name, &dst_ip);
		return;
	}

	do {
		dprintk("mpoa: (%s) ingress_purge_rcvd: removing an ingress entry, ip = %pI4\n",
			mpc->dev->name, &dst_ip);
		write_lock_bh(&mpc->ingress_lock);
		mpc->in_ops->remove_entry(entry, mpc);
		write_unlock_bh(&mpc->ingress_lock);
		mpc->in_ops->put(entry);
		entry = mpc->in_ops->get_with_mask(dst_ip, mpc, mask);
	} while (entry != NULL);

	return;
}