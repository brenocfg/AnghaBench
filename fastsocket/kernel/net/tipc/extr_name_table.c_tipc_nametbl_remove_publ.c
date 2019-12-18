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
typedef  int /*<<< orphan*/  u32 ;
struct publication {int dummy; } ;
struct name_seq {struct name_seq* sseqs; int /*<<< orphan*/  ns_list; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  first_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct name_seq*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct name_seq* nametbl_find_seq (int /*<<< orphan*/ ) ; 
 struct publication* tipc_nameseq_remove_publ (struct name_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct publication *tipc_nametbl_remove_publ(u32 type, u32 lower,
					     u32 node, u32 ref, u32 key)
{
	struct publication *publ;
	struct name_seq *seq = nametbl_find_seq(type);

	if (!seq)
		return NULL;

	dbg("Withdrawing {%u,%u} from 0x%x\n", type, lower, node);
	publ = tipc_nameseq_remove_publ(seq, lower, node, ref, key);

	if (!seq->first_free && list_empty(&seq->subscriptions)) {
		hlist_del_init(&seq->ns_list);
		kfree(seq->sseqs);
		kfree(seq);
	}
	return publ;
}