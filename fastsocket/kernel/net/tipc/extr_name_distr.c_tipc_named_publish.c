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
struct sk_buff {int dummy; } ;
struct publication {int /*<<< orphan*/  local_list; } ;
struct distr_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_SIZE ; 
 int /*<<< orphan*/  PUBLICATION ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ msg_data (int /*<<< orphan*/ ) ; 
 struct sk_buff* named_prepare_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  publ_cnt ; 
 int /*<<< orphan*/  publ_root ; 
 int /*<<< orphan*/  publ_to_item (struct distr_item*,struct publication*) ; 
 int /*<<< orphan*/  tipc_cltr_broadcast (struct sk_buff*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_named_publish(struct publication *publ)
{
	struct sk_buff *buf;
	struct distr_item *item;

	list_add_tail(&publ->local_list, &publ_root);
	publ_cnt++;

	buf = named_prepare_buf(PUBLICATION, ITEM_SIZE, 0);
	if (!buf) {
		warn("Publication distribution failure\n");
		return;
	}

	item = (struct distr_item *)msg_data(buf_msg(buf));
	publ_to_item(item, publ);
	dbg("tipc_named_withdraw: broadcasting publish msg\n");
	tipc_cltr_broadcast(buf);
}