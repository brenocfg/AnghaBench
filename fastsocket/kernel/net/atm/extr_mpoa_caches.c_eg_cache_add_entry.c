#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mpoa_client {int /*<<< orphan*/  egress_lock; int /*<<< orphan*/  mps_ctrl_addr; TYPE_3__* eg_cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  mps_ip; int /*<<< orphan*/  cache_id; int /*<<< orphan*/  eg_dst_ip; } ;
struct TYPE_6__ {TYPE_2__ eg_info; } ;
struct k_message {TYPE_1__ content; } ;
struct TYPE_8__ {int /*<<< orphan*/  use; TYPE_2__ ctrl_info; int /*<<< orphan*/  entry_state; int /*<<< orphan*/  tv; int /*<<< orphan*/  MPS_ctrl_ATM_addr; struct TYPE_8__* prev; struct TYPE_8__* next; } ;
typedef  TYPE_3__ eg_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 int /*<<< orphan*/  EGRESS_RESOLVED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static eg_cache_entry *eg_cache_add_entry(struct k_message *msg, struct mpoa_client *client)
{
	eg_cache_entry *entry = kzalloc(sizeof(eg_cache_entry), GFP_KERNEL);

	if (entry == NULL) {
		printk("mpoa: mpoa_caches.c: new_eg_cache_entry: out of memory\n");
		return NULL;
	}

	dprintk("mpoa: mpoa_caches.c: adding an egress entry, ip = %pI4, this should be our IP\n",
		&msg->content.eg_info.eg_dst_ip);

	atomic_set(&entry->use, 1);
	dprintk("mpoa: mpoa_caches.c: new_eg_cache_entry: about to lock\n");
	write_lock_irq(&client->egress_lock);
	entry->next = client->eg_cache;
	entry->prev = NULL;
	if (client->eg_cache != NULL)
		client->eg_cache->prev = entry;
	client->eg_cache = entry;

	memcpy(entry->MPS_ctrl_ATM_addr, client->mps_ctrl_addr, ATM_ESA_LEN);
	entry->ctrl_info = msg->content.eg_info;
	do_gettimeofday(&(entry->tv));
	entry->entry_state = EGRESS_RESOLVED;
	dprintk("mpoa: mpoa_caches.c: new_eg_cache_entry cache_id %lu\n", ntohl(entry->ctrl_info.cache_id));
	dprintk("mpoa: mpoa_caches.c: mps_ip = %pI4\n",
		&entry->ctrl_info.mps_ip);
	atomic_inc(&entry->use);

	write_unlock_irq(&client->egress_lock);
	dprintk("mpoa: mpoa_caches.c: new_eg_cache_entry: unlocked\n");

	return entry;
}