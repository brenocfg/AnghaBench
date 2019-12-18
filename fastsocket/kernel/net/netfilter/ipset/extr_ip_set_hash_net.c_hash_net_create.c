#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct ip_set_hash_nets {int dummy; } ;
struct ip_set_hash {TYPE_1__* table; scalar_t__ maxelem; int /*<<< orphan*/  timeout; int /*<<< orphan*/  initval; } ;
struct ip_set {scalar_t__ family; struct ip_set_hash* data; int /*<<< orphan*/  name; int /*<<< orphan*/ * variant; } ;
struct TYPE_3__ {int /*<<< orphan*/  htable_bits; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IPSET_ATTR_HASHSIZE ; 
 size_t IPSET_ATTR_MAXELEM ; 
 size_t IPSET_ATTR_TIMEOUT ; 
 scalar_t__ IPSET_DEFAULT_HASHSIZE ; 
 scalar_t__ IPSET_DEFAULT_MAXELEM ; 
 int IPSET_ERR_INVALID_FAMILY ; 
 int IPSET_ERR_PROTOCOL ; 
 scalar_t__ IPSET_MIMINAL_HASHSIZE ; 
 int /*<<< orphan*/  IPSET_NO_TIMEOUT ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hash_net4_gc_init (struct ip_set*) ; 
 int /*<<< orphan*/  hash_net4_tvariant ; 
 int /*<<< orphan*/  hash_net4_variant ; 
 int /*<<< orphan*/  hash_net6_gc_init (struct ip_set*) ; 
 int /*<<< orphan*/  hash_net6_tvariant ; 
 int /*<<< orphan*/  hash_net6_variant ; 
 int /*<<< orphan*/  htable_bits (scalar_t__) ; 
 size_t htable_size (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_set_alloc (size_t) ; 
 scalar_t__ ip_set_get_h32 (struct nlattr*) ; 
 int /*<<< orphan*/  ip_set_optattr_netorder (struct nlattr**,size_t) ; 
 int /*<<< orphan*/  ip_set_timeout_uget (struct nlattr*) ; 
 int /*<<< orphan*/  jhash_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_set_hash*) ; 
 struct ip_set_hash* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct ip_set_hash*,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
hash_net_create(struct ip_set *set, struct nlattr *tb[], u32 flags)
{
	u32 hashsize = IPSET_DEFAULT_HASHSIZE, maxelem = IPSET_DEFAULT_MAXELEM;
	struct ip_set_hash *h;
	u8 hbits;
	size_t hsize;

	if (!(set->family == AF_INET || set->family == AF_INET6))
		return -IPSET_ERR_INVALID_FAMILY;

	if (unlikely(!ip_set_optattr_netorder(tb, IPSET_ATTR_HASHSIZE) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_MAXELEM) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT)))
		return -IPSET_ERR_PROTOCOL;

	if (tb[IPSET_ATTR_HASHSIZE]) {
		hashsize = ip_set_get_h32(tb[IPSET_ATTR_HASHSIZE]);
		if (hashsize < IPSET_MIMINAL_HASHSIZE)
			hashsize = IPSET_MIMINAL_HASHSIZE;
	}

	if (tb[IPSET_ATTR_MAXELEM])
		maxelem = ip_set_get_h32(tb[IPSET_ATTR_MAXELEM]);

	h = kzalloc(sizeof(*h)
		    + sizeof(struct ip_set_hash_nets)
		      * (set->family == AF_INET ? 32 : 128), GFP_KERNEL);
	if (!h)
		return -ENOMEM;

	h->maxelem = maxelem;
	get_random_bytes(&h->initval, sizeof(h->initval));
	h->timeout = IPSET_NO_TIMEOUT;

	hbits = htable_bits(hashsize);
	hsize = htable_size(hbits);
	if (hsize == 0) {
		kfree(h);
		return -ENOMEM;
	}
	h->table = ip_set_alloc(hsize);
	if (!h->table) {
		kfree(h);
		return -ENOMEM;
	}
	h->table->htable_bits = hbits;

	set->data = h;

	if (tb[IPSET_ATTR_TIMEOUT]) {
		h->timeout = ip_set_timeout_uget(tb[IPSET_ATTR_TIMEOUT]);

		set->variant = set->family == AF_INET
			? &hash_net4_tvariant : &hash_net6_tvariant;

		if (set->family == AF_INET)
			hash_net4_gc_init(set);
		else
			hash_net6_gc_init(set);
	} else {
		set->variant = set->family == AF_INET
			? &hash_net4_variant : &hash_net6_variant;
	}

	pr_debug("create %s hashsize %u (%u) maxelem %u: %p(%p)\n",
		 set->name, jhash_size(h->table->htable_bits),
		 h->table->htable_bits, h->maxelem, set->data, h->table);

	return 0;
}