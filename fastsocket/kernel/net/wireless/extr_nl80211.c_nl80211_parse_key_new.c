#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct TYPE_2__ {void* cipher; void* seq_len; void* seq; void* key_len; void* key; } ;
struct key_parse {int def; int defmgmt; int def_uni; int def_multi; scalar_t__ type; TYPE_1__ p; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_KEY_CIPHER ; 
 size_t NL80211_KEY_DATA ; 
 size_t NL80211_KEY_DEFAULT ; 
 size_t NL80211_KEY_DEFAULT_MGMT ; 
 size_t NL80211_KEY_DEFAULT_TYPES ; 
 size_t NL80211_KEY_DEFAULT_TYPE_MULTICAST ; 
 size_t NL80211_KEY_DEFAULT_TYPE_UNICAST ; 
 size_t NL80211_KEY_IDX ; 
 int NL80211_KEY_MAX ; 
 size_t NL80211_KEY_SEQ ; 
 size_t NL80211_KEY_TYPE ; 
 scalar_t__ NUM_NL80211_KEYTYPES ; 
 int NUM_NL80211_KEY_DEFAULT_TYPES ; 
 int /*<<< orphan*/  nl80211_key_default_policy ; 
 int /*<<< orphan*/  nl80211_key_policy ; 
 void* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 void* nla_len (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_parse_key_new(struct nlattr *key, struct key_parse *k)
{
	struct nlattr *tb[NL80211_KEY_MAX + 1];
	int err = nla_parse_nested(tb, NL80211_KEY_MAX, key,
				   nl80211_key_policy);
	if (err)
		return err;

	k->def = !!tb[NL80211_KEY_DEFAULT];
	k->defmgmt = !!tb[NL80211_KEY_DEFAULT_MGMT];

	if (k->def) {
		k->def_uni = true;
		k->def_multi = true;
	}
	if (k->defmgmt)
		k->def_multi = true;

	if (tb[NL80211_KEY_IDX])
		k->idx = nla_get_u8(tb[NL80211_KEY_IDX]);

	if (tb[NL80211_KEY_DATA]) {
		k->p.key = nla_data(tb[NL80211_KEY_DATA]);
		k->p.key_len = nla_len(tb[NL80211_KEY_DATA]);
	}

	if (tb[NL80211_KEY_SEQ]) {
		k->p.seq = nla_data(tb[NL80211_KEY_SEQ]);
		k->p.seq_len = nla_len(tb[NL80211_KEY_SEQ]);
	}

	if (tb[NL80211_KEY_CIPHER])
		k->p.cipher = nla_get_u32(tb[NL80211_KEY_CIPHER]);

	if (tb[NL80211_KEY_TYPE]) {
		k->type = nla_get_u32(tb[NL80211_KEY_TYPE]);
		if (k->type < 0 || k->type >= NUM_NL80211_KEYTYPES)
			return -EINVAL;
	}

	if (tb[NL80211_KEY_DEFAULT_TYPES]) {
		struct nlattr *kdt[NUM_NL80211_KEY_DEFAULT_TYPES];
		err = nla_parse_nested(kdt, NUM_NL80211_KEY_DEFAULT_TYPES - 1,
				       tb[NL80211_KEY_DEFAULT_TYPES],
				       nl80211_key_default_policy);
		if (err)
			return err;

		k->def_uni = kdt[NL80211_KEY_DEFAULT_TYPE_UNICAST];
		k->def_multi = kdt[NL80211_KEY_DEFAULT_TYPE_MULTICAST];
	}

	return 0;
}