#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {TYPE_4__* in_ops; TYPE_3__* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  in_dst_ip; } ;
struct TYPE_13__ {TYPE_1__ in_info; } ;
struct k_message {TYPE_2__ content; } ;
struct TYPE_16__ {scalar_t__ entry_state; scalar_t__ shortcut; scalar_t__ refresh_time; int /*<<< orphan*/  reply_wait; int /*<<< orphan*/  tv; TYPE_1__ ctrl_info; } ;
typedef  TYPE_5__ in_cache_entry ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_15__ {int /*<<< orphan*/  (* put ) (TYPE_5__*) ;TYPE_5__* (* get ) (int /*<<< orphan*/ ,struct mpoa_client*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ INGRESS_RESOLVED ; 
 scalar_t__ INGRESS_RESOLVING ; 
 int /*<<< orphan*/  check_qos_and_open_shortcut (struct k_message*,struct mpoa_client*,TYPE_5__*) ; 
 int /*<<< orphan*/  ddprintk (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* stub1 (int /*<<< orphan*/ ,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*) ; 

__attribute__((used)) static void MPOA_res_reply_rcvd(struct k_message *msg, struct mpoa_client *mpc)
{
	__be32 dst_ip = msg->content.in_info.in_dst_ip;
	in_cache_entry *entry = mpc->in_ops->get(dst_ip, mpc);

	dprintk("mpoa: (%s) MPOA_res_reply_rcvd: ip %pI4\n",
		mpc->dev->name, &dst_ip);
	ddprintk("mpoa: (%s) MPOA_res_reply_rcvd() entry = %p", mpc->dev->name, entry);
	if(entry == NULL){
		printk("\nmpoa: (%s) ARGH, received res. reply for an entry that doesn't exist.\n", mpc->dev->name);
		return;
	}
	ddprintk(" entry_state = %d ", entry->entry_state);

	if (entry->entry_state == INGRESS_RESOLVED) {
		printk("\nmpoa: (%s) MPOA_res_reply_rcvd for RESOLVED entry!\n", mpc->dev->name);
		mpc->in_ops->put(entry);
		return;
	}

	entry->ctrl_info = msg->content.in_info;
	do_gettimeofday(&(entry->tv));
	do_gettimeofday(&(entry->reply_wait)); /* Used in refreshing func from now on */
	entry->refresh_time = 0;
	ddprintk("entry->shortcut = %p\n", entry->shortcut);

	if(entry->entry_state == INGRESS_RESOLVING && entry->shortcut != NULL){
		entry->entry_state = INGRESS_RESOLVED;
		mpc->in_ops->put(entry);
		return; /* Shortcut already open... */
	}

	if (entry->shortcut != NULL) {
		printk("mpoa: (%s) MPOA_res_reply_rcvd: entry->shortcut != NULL, impossible!\n",
		       mpc->dev->name);
		mpc->in_ops->put(entry);
		return;
	}

	check_qos_and_open_shortcut(msg, mpc, entry);
	entry->entry_state = INGRESS_RESOLVED;
	mpc->in_ops->put(entry);

	return;

}