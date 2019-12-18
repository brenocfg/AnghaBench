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
struct xt_target_param {unsigned int hooknum; int /*<<< orphan*/  targinfo; TYPE_1__* target; struct net_device const* out; struct net_device const* in; int /*<<< orphan*/  family; } ;
struct xt_match_param {int* hotdrop; unsigned int hooknum; struct net_device const* out; struct net_device const* in; int /*<<< orphan*/  family; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct ebt_table_info {char* entries; struct ebt_entries** hook_entry; struct ebt_chainstack** chainstack; int /*<<< orphan*/  nentries; int /*<<< orphan*/  counters; } ;
struct ebt_table {int /*<<< orphan*/  lock; struct ebt_table_info* private; } ;
struct ebt_standard_target {int verdict; } ;
struct TYPE_4__ {TYPE_1__* target; } ;
struct ebt_entry_target {TYPE_2__ u; int /*<<< orphan*/  data; } ;
struct ebt_entry {int target_offset; } ;
struct ebt_entries {int nentries; int counter_offset; int policy; scalar_t__ data; scalar_t__ distinguisher; } ;
struct ebt_counter {int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; } ;
struct ebt_chainstack {int n; struct ebt_entry* e; struct ebt_entries* chaininfo; } ;
struct TYPE_3__ {int (* target ) (struct sk_buff*,struct xt_target_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUGPRINT (char*) ; 
 struct ebt_counter* COUNTER_BASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int EBT_ACCEPT ; 
 int EBT_CONTINUE ; 
 int EBT_DROP ; 
 scalar_t__ EBT_MATCH_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,struct sk_buff*,struct xt_match_param*) ; 
 int EBT_RETURN ; 
 int /*<<< orphan*/  EBT_WATCHER_ITERATE (struct ebt_entry*,int /*<<< orphan*/ ,struct sk_buff*,struct xt_target_param*) ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 scalar_t__ ebt_basic_match (struct ebt_entry*,int /*<<< orphan*/ ,struct net_device const*,struct net_device const*) ; 
 int /*<<< orphan*/  ebt_do_match ; 
 int /*<<< orphan*/  ebt_do_watcher ; 
 void* ebt_next_entry (struct ebt_entry*) ; 
 int /*<<< orphan*/  eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 size_t smp_processor_id () ; 
 int stub1 (struct sk_buff*,struct xt_target_param*) ; 

unsigned int ebt_do_table (unsigned int hook, struct sk_buff *skb,
   const struct net_device *in, const struct net_device *out,
   struct ebt_table *table)
{
	int i, nentries;
	struct ebt_entry *point;
	struct ebt_counter *counter_base, *cb_base;
	struct ebt_entry_target *t;
	int verdict, sp = 0;
	struct ebt_chainstack *cs;
	struct ebt_entries *chaininfo;
	char *base;
	struct ebt_table_info *private;
	bool hotdrop = false;
	struct xt_match_param mtpar;
	struct xt_target_param tgpar;

	mtpar.family  = tgpar.family = NFPROTO_BRIDGE;
	mtpar.in      = tgpar.in  = in;
	mtpar.out     = tgpar.out = out;
	mtpar.hotdrop = &hotdrop;
	mtpar.hooknum = tgpar.hooknum = hook;

	read_lock_bh(&table->lock);
	private = table->private;
	cb_base = COUNTER_BASE(private->counters, private->nentries,
	   smp_processor_id());
	if (private->chainstack)
		cs = private->chainstack[smp_processor_id()];
	else
		cs = NULL;
	chaininfo = private->hook_entry[hook];
	nentries = private->hook_entry[hook]->nentries;
	point = (struct ebt_entry *)(private->hook_entry[hook]->data);
	counter_base = cb_base + private->hook_entry[hook]->counter_offset;
	/* base for chain jumps */
	base = private->entries;
	i = 0;
	while (i < nentries) {
		if (ebt_basic_match(point, eth_hdr(skb), in, out))
			goto letscontinue;

		if (EBT_MATCH_ITERATE(point, ebt_do_match, skb, &mtpar) != 0)
			goto letscontinue;
		if (hotdrop) {
			read_unlock_bh(&table->lock);
			return NF_DROP;
		}

		/* increase counter */
		(*(counter_base + i)).pcnt++;
		(*(counter_base + i)).bcnt += skb->len;

		/* these should only watch: not modify, nor tell us
		   what to do with the packet */
		EBT_WATCHER_ITERATE(point, ebt_do_watcher, skb, &tgpar);

		t = (struct ebt_entry_target *)
		   (((char *)point) + point->target_offset);
		/* standard target */
		if (!t->u.target->target)
			verdict = ((struct ebt_standard_target *)t)->verdict;
		else {
			tgpar.target   = t->u.target;
			tgpar.targinfo = t->data;
			verdict = t->u.target->target(skb, &tgpar);
		}
		if (verdict == EBT_ACCEPT) {
			read_unlock_bh(&table->lock);
			return NF_ACCEPT;
		}
		if (verdict == EBT_DROP) {
			read_unlock_bh(&table->lock);
			return NF_DROP;
		}
		if (verdict == EBT_RETURN) {
letsreturn:
#ifdef CONFIG_NETFILTER_DEBUG
			if (sp == 0) {
				BUGPRINT("RETURN on base chain");
				/* act like this is EBT_CONTINUE */
				goto letscontinue;
			}
#endif
			sp--;
			/* put all the local variables right */
			i = cs[sp].n;
			chaininfo = cs[sp].chaininfo;
			nentries = chaininfo->nentries;
			point = cs[sp].e;
			counter_base = cb_base +
			   chaininfo->counter_offset;
			continue;
		}
		if (verdict == EBT_CONTINUE)
			goto letscontinue;
#ifdef CONFIG_NETFILTER_DEBUG
		if (verdict < 0) {
			BUGPRINT("bogus standard verdict\n");
			read_unlock_bh(&table->lock);
			return NF_DROP;
		}
#endif
		/* jump to a udc */
		cs[sp].n = i + 1;
		cs[sp].chaininfo = chaininfo;
		cs[sp].e = ebt_next_entry(point);
		i = 0;
		chaininfo = (struct ebt_entries *) (base + verdict);
#ifdef CONFIG_NETFILTER_DEBUG
		if (chaininfo->distinguisher) {
			BUGPRINT("jump to non-chain\n");
			read_unlock_bh(&table->lock);
			return NF_DROP;
		}
#endif
		nentries = chaininfo->nentries;
		point = (struct ebt_entry *)chaininfo->data;
		counter_base = cb_base + chaininfo->counter_offset;
		sp++;
		continue;
letscontinue:
		point = ebt_next_entry(point);
		i++;
	}

	/* I actually like this :) */
	if (chaininfo->policy == EBT_RETURN)
		goto letsreturn;
	if (chaininfo->policy == EBT_ACCEPT) {
		read_unlock_bh(&table->lock);
		return NF_ACCEPT;
	}
	read_unlock_bh(&table->lock);
	return NF_DROP;
}