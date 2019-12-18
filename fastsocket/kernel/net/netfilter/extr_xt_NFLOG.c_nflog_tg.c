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
struct xt_target_param {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  hooknum; int /*<<< orphan*/  family; struct xt_nflog_info* targinfo; } ;
struct xt_nflog_info {int /*<<< orphan*/  prefix; int /*<<< orphan*/  threshold; int /*<<< orphan*/  group; int /*<<< orphan*/  len; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qthreshold; int /*<<< orphan*/  group; int /*<<< orphan*/  copy_len; } ;
struct TYPE_4__ {TYPE_1__ ulog; } ;
struct nf_loginfo {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_LOG_TYPE_ULOG ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  nfulnl_log_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_loginfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
nflog_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_nflog_info *info = par->targinfo;
	struct nf_loginfo li;

	li.type		     = NF_LOG_TYPE_ULOG;
	li.u.ulog.copy_len   = info->len;
	li.u.ulog.group	     = info->group;
	li.u.ulog.qthreshold = info->threshold;

	nfulnl_log_packet(par->family, par->hooknum, skb, par->in,
			  par->out, &li, info->prefix);
	return XT_CONTINUE;
}