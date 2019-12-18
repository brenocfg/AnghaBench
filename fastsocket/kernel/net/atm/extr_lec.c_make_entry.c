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
struct lec_priv {int dummy; } ;
struct lec_arp_table {int /*<<< orphan*/  usage; int /*<<< orphan*/  tx_wait; struct lec_priv* priv; int /*<<< orphan*/  last_used; int /*<<< orphan*/  timer; int /*<<< orphan*/  next; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jiffies ; 
 struct lec_arp_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lec_arp_expire_arp ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lec_arp_table *make_entry(struct lec_priv *priv,
					const unsigned char *mac_addr)
{
	struct lec_arp_table *to_return;

	to_return = kzalloc(sizeof(struct lec_arp_table), GFP_ATOMIC);
	if (!to_return) {
		printk("LEC: Arp entry kmalloc failed\n");
		return NULL;
	}
	memcpy(to_return->mac_addr, mac_addr, ETH_ALEN);
	INIT_HLIST_NODE(&to_return->next);
	setup_timer(&to_return->timer, lec_arp_expire_arp,
			(unsigned long)to_return);
	to_return->last_used = jiffies;
	to_return->priv = priv;
	skb_queue_head_init(&to_return->tx_wait);
	atomic_set(&to_return->usage, 1);
	return to_return;
}