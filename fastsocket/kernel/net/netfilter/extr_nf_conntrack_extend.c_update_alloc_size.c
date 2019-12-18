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
struct nf_ct_ext_type {int flags; int id; int alloc_size; int len; int /*<<< orphan*/  align; } ;
struct nf_ct_ext {int dummy; } ;
typedef  enum nf_ct_ext_id { ____Placeholder_nf_ct_ext_id } nf_ct_ext_id ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int NF_CT_EXT_F_PREALLOC ; 
 int NF_CT_EXT_NUM ; 
 struct nf_ct_ext_type** nf_ct_ext_types ; 

__attribute__((used)) static void update_alloc_size(struct nf_ct_ext_type *type)
{
	int i, j;
	struct nf_ct_ext_type *t1, *t2;
	enum nf_ct_ext_id min = 0, max = NF_CT_EXT_NUM - 1;

	/* unnecessary to update all types */
	if ((type->flags & NF_CT_EXT_F_PREALLOC) == 0) {
		min = type->id;
		max = type->id;
	}

	/* This assumes that extended areas in conntrack for the types
	   whose NF_CT_EXT_F_PREALLOC bit set are allocated in order */
	for (i = min; i <= max; i++) {
		t1 = nf_ct_ext_types[i];
		if (!t1)
			continue;

		t1->alloc_size = sizeof(struct nf_ct_ext)
				 + ALIGN(sizeof(struct nf_ct_ext), t1->align)
				 + t1->len;
		for (j = 0; j < NF_CT_EXT_NUM; j++) {
			t2 = nf_ct_ext_types[j];
			if (t2 == NULL || t2 == t1 ||
			    (t2->flags & NF_CT_EXT_F_PREALLOC) == 0)
				continue;

			t1->alloc_size = ALIGN(t1->alloc_size, t2->align)
					 + t2->len;
		}
	}
}