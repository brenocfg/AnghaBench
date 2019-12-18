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
struct nf_ct_ext_type {int len; int /*<<< orphan*/  (* move ) (void*,void*) ;int /*<<< orphan*/  align; } ;
struct nf_ct_ext {int len; int* offset; int /*<<< orphan*/  rcu; } ;
struct nf_conn {struct nf_ct_ext* ext; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nf_ct_ext_id { ____Placeholder_nf_ct_ext_id } nf_ct_ext_id ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int NF_CT_EXT_NUM ; 
 struct nf_ct_ext* __krealloc (struct nf_ct_ext*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nf_ct_ext_free_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* nf_ct_ext_create (struct nf_ct_ext**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_ext_exist (struct nf_conn*,int) ; 
 int /*<<< orphan*/ * nf_ct_ext_types ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 struct nf_ct_ext_type* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (void*,void*) ; 

void *__nf_ct_ext_add(struct nf_conn *ct, enum nf_ct_ext_id id, gfp_t gfp)
{
	struct nf_ct_ext *new;
	int i, newlen, newoff;
	struct nf_ct_ext_type *t;

	/* Conntrack must not be confirmed to avoid races on reallocation. */
	NF_CT_ASSERT(!nf_ct_is_confirmed(ct));

	if (!ct->ext)
		return nf_ct_ext_create(&ct->ext, id, gfp);

	if (nf_ct_ext_exist(ct, id))
		return NULL;

	rcu_read_lock();
	t = rcu_dereference(nf_ct_ext_types[id]);
	BUG_ON(t == NULL);

	newoff = ALIGN(ct->ext->len, t->align);
	newlen = newoff + t->len;
	rcu_read_unlock();

	new = __krealloc(ct->ext, newlen, gfp);
	if (!new)
		return NULL;

	if (new != ct->ext) {
		for (i = 0; i < NF_CT_EXT_NUM; i++) {
			if (!nf_ct_ext_exist(ct, i))
				continue;

			rcu_read_lock();
			t = rcu_dereference(nf_ct_ext_types[i]);
			if (t && t->move)
				t->move((void *)new + new->offset[i],
					(void *)ct->ext + ct->ext->offset[i]);
			rcu_read_unlock();
		}
		call_rcu(&ct->ext->rcu, __nf_ct_ext_free_rcu);
		ct->ext = new;
	}

	new->offset[id] = newoff;
	new->len = newlen;
	memset((void *)new + newoff, 0, newlen - newoff);
	return (void *)new + newoff;
}