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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct pf_rule {int /*<<< orphan*/  proto; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  op; int /*<<< orphan*/ * gid; } ;
struct TYPE_3__ {int /*<<< orphan*/  op; int /*<<< orphan*/ * uid; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  PF_MD5_UPD (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_MD5_UPD_HTONL (struct pf_rule*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_MD5_UPD_HTONS (struct pf_rule*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_MD5_UPD_STR (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action ; 
 int /*<<< orphan*/  af ; 
 int /*<<< orphan*/  allow_opts ; 
 int /*<<< orphan*/  code ; 
 int /*<<< orphan*/  direction ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  flagset ; 
 TYPE_2__ gid ; 
 int /*<<< orphan*/  ifname ; 
 int /*<<< orphan*/  ifnot ; 
 int /*<<< orphan*/  keep_state ; 
 int /*<<< orphan*/  label ; 
 int /*<<< orphan*/  match_tag ; 
 int /*<<< orphan*/  match_tag_not ; 
 int /*<<< orphan*/  match_tagname ; 
 int /*<<< orphan*/  natpass ; 
 int /*<<< orphan*/  os_fingerprint ; 
 int /*<<< orphan*/  pf_hash_rule_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prob ; 
 int /*<<< orphan*/  proto ; 
 int /*<<< orphan*/  quick ; 
 int /*<<< orphan*/  rt ; 
 int /*<<< orphan*/  rule_flag ; 
 int /*<<< orphan*/  tos ; 
 int /*<<< orphan*/  type ; 
 TYPE_1__ uid ; 

__attribute__((used)) static void
pf_hash_rule(MD5_CTX *ctx, struct pf_rule *rule)
{
	u_int16_t x;
	u_int32_t y;

	pf_hash_rule_addr(ctx, &rule->src, rule->proto);
	pf_hash_rule_addr(ctx, &rule->dst, rule->proto);
	PF_MD5_UPD_STR(rule, label);
	PF_MD5_UPD_STR(rule, ifname);
	PF_MD5_UPD_STR(rule, match_tagname);
	PF_MD5_UPD_HTONS(rule, match_tag, x); /* dup? */
	PF_MD5_UPD_HTONL(rule, os_fingerprint, y);
	PF_MD5_UPD_HTONL(rule, prob, y);
	PF_MD5_UPD_HTONL(rule, uid.uid[0], y);
	PF_MD5_UPD_HTONL(rule, uid.uid[1], y);
	PF_MD5_UPD(rule, uid.op);
	PF_MD5_UPD_HTONL(rule, gid.gid[0], y);
	PF_MD5_UPD_HTONL(rule, gid.gid[1], y);
	PF_MD5_UPD(rule, gid.op);
	PF_MD5_UPD_HTONL(rule, rule_flag, y);
	PF_MD5_UPD(rule, action);
	PF_MD5_UPD(rule, direction);
	PF_MD5_UPD(rule, af);
	PF_MD5_UPD(rule, quick);
	PF_MD5_UPD(rule, ifnot);
	PF_MD5_UPD(rule, match_tag_not);
	PF_MD5_UPD(rule, natpass);
	PF_MD5_UPD(rule, keep_state);
	PF_MD5_UPD(rule, proto);
	PF_MD5_UPD(rule, type);
	PF_MD5_UPD(rule, code);
	PF_MD5_UPD(rule, flags);
	PF_MD5_UPD(rule, flagset);
	PF_MD5_UPD(rule, allow_opts);
	PF_MD5_UPD(rule, rt);
	PF_MD5_UPD(rule, tos);
}