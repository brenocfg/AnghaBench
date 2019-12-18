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
struct ts_state {int dummy; } ;
struct text_match {int /*<<< orphan*/  config; scalar_t__ to_offset; int /*<<< orphan*/  to_layer; scalar_t__ from_offset; int /*<<< orphan*/  from_layer; } ;
struct tcf_pkt_info {int dummy; } ;
struct tcf_ematch {int dummy; } ;
struct sk_buff {int data; } ;

/* Variables and functions */
 struct text_match* EM_TEXT_PRIV (struct tcf_ematch*) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ skb_find_text (struct sk_buff*,int,int,int /*<<< orphan*/ ,struct ts_state*) ; 
 int tcf_get_base_ptr (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_text_match(struct sk_buff *skb, struct tcf_ematch *m,
			 struct tcf_pkt_info *info)
{
	struct text_match *tm = EM_TEXT_PRIV(m);
	int from, to;
	struct ts_state state;

	from = tcf_get_base_ptr(skb, tm->from_layer) - skb->data;
	from += tm->from_offset;

	to = tcf_get_base_ptr(skb, tm->to_layer) - skb->data;
	to += tm->to_offset;

	return skb_find_text(skb, from, to, tm->config, &state) != UINT_MAX;
}