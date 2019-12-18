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
struct flowi {scalar_t__ fld_scope; int /*<<< orphan*/  fld_dst; } ;
struct dn_zone {int /*<<< orphan*/  dz_order; struct dn_zone* dz_next; } ;
struct dn_hash {struct dn_zone* dh_zone_list; } ;
struct dn_fib_table {scalar_t__ data; } ;
struct dn_fib_res {scalar_t__ scope; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  type; } ;
struct dn_fib_node {int fn_state; scalar_t__ fn_scope; int /*<<< orphan*/  fn_type; int /*<<< orphan*/  fn_key; struct dn_fib_node* fn_next; } ;
typedef  int /*<<< orphan*/  dn_fib_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  DN_FIB_INFO (struct dn_fib_node*) ; 
 int DN_S_ACCESSED ; 
 int DN_S_ZOMBIE ; 
 int dn_fib_semantic_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flowi const*,struct dn_fib_res*) ; 
 int /*<<< orphan*/  dn_fib_tables_lock ; 
 int /*<<< orphan*/  dn_key_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dn_key_leq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dn_fib_node* dz_chain (int /*<<< orphan*/ ,struct dn_zone*) ; 
 int /*<<< orphan*/  dz_key (int /*<<< orphan*/ ,struct dn_zone*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dn_fib_table_lookup(struct dn_fib_table *tb, const struct flowi *flp, struct dn_fib_res *res)
{
	int err;
	struct dn_zone *dz;
	struct dn_hash *t = (struct dn_hash *)tb->data;

	read_lock(&dn_fib_tables_lock);
	for(dz = t->dh_zone_list; dz; dz = dz->dz_next) {
		struct dn_fib_node *f;
		dn_fib_key_t k = dz_key(flp->fld_dst, dz);

		for(f = dz_chain(k, dz); f; f = f->fn_next) {
			if (!dn_key_eq(k, f->fn_key)) {
				if (dn_key_leq(k, f->fn_key))
					break;
				else
					continue;
			}

			f->fn_state |= DN_S_ACCESSED;

			if (f->fn_state&DN_S_ZOMBIE)
				continue;

			if (f->fn_scope < flp->fld_scope)
				continue;

			err = dn_fib_semantic_match(f->fn_type, DN_FIB_INFO(f), flp, res);

			if (err == 0) {
				res->type = f->fn_type;
				res->scope = f->fn_scope;
				res->prefixlen = dz->dz_order;
				goto out;
			}
			if (err < 0)
				goto out;
		}
	}
	err = 1;
out:
	read_unlock(&dn_fib_tables_lock);
	return err;
}