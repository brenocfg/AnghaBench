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
struct nf_ct_ext_type {unsigned int len; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  align; } ;
struct nf_ct_ext {unsigned int* offset; unsigned int len; int /*<<< orphan*/  rcu; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nf_ct_ext_id { ____Placeholder_nf_ct_ext_id } nf_ct_ext_id ;

/* Variables and functions */
 unsigned int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RCU_HEAD (int /*<<< orphan*/ *) ; 
 struct nf_ct_ext* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nf_ct_ext_types ; 
 struct nf_ct_ext_type* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void *
nf_ct_ext_create(struct nf_ct_ext **ext, enum nf_ct_ext_id id, gfp_t gfp)
{
	unsigned int off, len;
	struct nf_ct_ext_type *t;

	rcu_read_lock();
	t = rcu_dereference(nf_ct_ext_types[id]);
	BUG_ON(t == NULL);
	off = ALIGN(sizeof(struct nf_ct_ext), t->align);
	len = off + t->len;
	rcu_read_unlock();

	*ext = kzalloc(t->alloc_size, gfp);
	if (!*ext)
		return NULL;

	INIT_RCU_HEAD(&(*ext)->rcu);
	(*ext)->offset[id] = off;
	(*ext)->len = len;

	return (void *)(*ext) + off;
}