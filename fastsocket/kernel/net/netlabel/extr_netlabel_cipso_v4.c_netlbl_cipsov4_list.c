#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct TYPE_8__ {TYPE_3__* std; } ;
struct cipso_v4_doi {size_t type; scalar_t__* tags; TYPE_4__ map; } ;
struct TYPE_6__ {size_t local_size; size_t* local; } ;
struct TYPE_5__ {size_t local_size; size_t* local; } ;
struct TYPE_7__ {TYPE_2__ cat; TYPE_1__ lvl; } ;

/* Variables and functions */
 size_t CIPSO_V4_INV_CAT ; 
 size_t CIPSO_V4_INV_LVL ; 
#define  CIPSO_V4_MAP_TRANS 128 
 scalar_t__ CIPSO_V4_TAG_INVALID ; 
 size_t CIPSO_V4_TAG_MAXCNT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NLBL_CIPSOV4_A_DOI ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSCAT ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSCATLOC ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSCATLST ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSCATREM ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSLVL ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSLVLLOC ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSLVLLST ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MLSLVLREM ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MTYPE ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_TAG ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_TAGLST ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_C_LIST ; 
 size_t NLMSG_DEFAULT_SIZE ; 
 struct cipso_v4_doi* cipso_v4_doi_getdef (size_t) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlbl_cipsov4_gnl_family ; 
 size_t nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* nlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int netlbl_cipsov4_list(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val;
	struct sk_buff *ans_skb = NULL;
	u32 nlsze_mult = 1;
	void *data;
	u32 doi;
	struct nlattr *nla_a;
	struct nlattr *nla_b;
	struct cipso_v4_doi *doi_def;
	u32 iter;

	if (!info->attrs[NLBL_CIPSOV4_A_DOI]) {
		ret_val = -EINVAL;
		goto list_failure;
	}

list_start:
	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE * nlsze_mult, GFP_KERNEL);
	if (ans_skb == NULL) {
		ret_val = -ENOMEM;
		goto list_failure;
	}
	data = genlmsg_put_reply(ans_skb, info, &netlbl_cipsov4_gnl_family,
				 0, NLBL_CIPSOV4_C_LIST);
	if (data == NULL) {
		ret_val = -ENOMEM;
		goto list_failure;
	}

	doi = nla_get_u32(info->attrs[NLBL_CIPSOV4_A_DOI]);

	rcu_read_lock();
	doi_def = cipso_v4_doi_getdef(doi);
	if (doi_def == NULL) {
		ret_val = -EINVAL;
		goto list_failure_lock;
	}

	ret_val = nla_put_u32(ans_skb, NLBL_CIPSOV4_A_MTYPE, doi_def->type);
	if (ret_val != 0)
		goto list_failure_lock;

	nla_a = nla_nest_start(ans_skb, NLBL_CIPSOV4_A_TAGLST);
	if (nla_a == NULL) {
		ret_val = -ENOMEM;
		goto list_failure_lock;
	}
	for (iter = 0;
	     iter < CIPSO_V4_TAG_MAXCNT &&
	       doi_def->tags[iter] != CIPSO_V4_TAG_INVALID;
	     iter++) {
		ret_val = nla_put_u8(ans_skb,
				     NLBL_CIPSOV4_A_TAG,
				     doi_def->tags[iter]);
		if (ret_val != 0)
			goto list_failure_lock;
	}
	nla_nest_end(ans_skb, nla_a);

	switch (doi_def->type) {
	case CIPSO_V4_MAP_TRANS:
		nla_a = nla_nest_start(ans_skb, NLBL_CIPSOV4_A_MLSLVLLST);
		if (nla_a == NULL) {
			ret_val = -ENOMEM;
			goto list_failure_lock;
		}
		for (iter = 0;
		     iter < doi_def->map.std->lvl.local_size;
		     iter++) {
			if (doi_def->map.std->lvl.local[iter] ==
			    CIPSO_V4_INV_LVL)
				continue;

			nla_b = nla_nest_start(ans_skb, NLBL_CIPSOV4_A_MLSLVL);
			if (nla_b == NULL) {
				ret_val = -ENOMEM;
				goto list_retry;
			}
			ret_val = nla_put_u32(ans_skb,
					      NLBL_CIPSOV4_A_MLSLVLLOC,
					      iter);
			if (ret_val != 0)
				goto list_retry;
			ret_val = nla_put_u32(ans_skb,
					    NLBL_CIPSOV4_A_MLSLVLREM,
					    doi_def->map.std->lvl.local[iter]);
			if (ret_val != 0)
				goto list_retry;
			nla_nest_end(ans_skb, nla_b);
		}
		nla_nest_end(ans_skb, nla_a);

		nla_a = nla_nest_start(ans_skb, NLBL_CIPSOV4_A_MLSCATLST);
		if (nla_a == NULL) {
			ret_val = -ENOMEM;
			goto list_retry;
		}
		for (iter = 0;
		     iter < doi_def->map.std->cat.local_size;
		     iter++) {
			if (doi_def->map.std->cat.local[iter] ==
			    CIPSO_V4_INV_CAT)
				continue;

			nla_b = nla_nest_start(ans_skb, NLBL_CIPSOV4_A_MLSCAT);
			if (nla_b == NULL) {
				ret_val = -ENOMEM;
				goto list_retry;
			}
			ret_val = nla_put_u32(ans_skb,
					      NLBL_CIPSOV4_A_MLSCATLOC,
					      iter);
			if (ret_val != 0)
				goto list_retry;
			ret_val = nla_put_u32(ans_skb,
					    NLBL_CIPSOV4_A_MLSCATREM,
					    doi_def->map.std->cat.local[iter]);
			if (ret_val != 0)
				goto list_retry;
			nla_nest_end(ans_skb, nla_b);
		}
		nla_nest_end(ans_skb, nla_a);

		break;
	}
	rcu_read_unlock();

	genlmsg_end(ans_skb, data);
	return genlmsg_reply(ans_skb, info);

list_retry:
	/* XXX - this limit is a guesstimate */
	if (nlsze_mult < 4) {
		rcu_read_unlock();
		kfree_skb(ans_skb);
		nlsze_mult *= 2;
		goto list_start;
	}
list_failure_lock:
	rcu_read_unlock();
list_failure:
	kfree_skb(ans_skb);
	return ret_val;
}