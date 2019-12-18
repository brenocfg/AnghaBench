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
struct xt_target_param {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  hooknum; struct ipt_log_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  logflags; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ log; } ;
struct nf_loginfo {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct ipt_log_info {int /*<<< orphan*/  prefix; int /*<<< orphan*/  logflags; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  ipt_log_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_loginfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
log_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ipt_log_info *loginfo = par->targinfo;
	struct nf_loginfo li;

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = loginfo->level;
	li.u.log.logflags = loginfo->logflags;

	ipt_log_packet(NFPROTO_IPV4, par->hooknum, skb, par->in, par->out, &li,
		       loginfo->prefix);
	return XT_CONTINUE;
}