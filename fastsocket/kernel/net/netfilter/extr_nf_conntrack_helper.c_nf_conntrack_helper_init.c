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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  helper_extend ; 
 int /*<<< orphan*/  nf_ct_alloc_hashtable (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nf_ct_extend_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_free_hashtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_helper_hash ; 
 int nf_ct_helper_hsize ; 
 int /*<<< orphan*/  nf_ct_helper_vmalloc ; 

int nf_conntrack_helper_init(void)
{
	int err;

	nf_ct_helper_hsize = 1; /* gets rounded up to use one page */
	nf_ct_helper_hash = nf_ct_alloc_hashtable(&nf_ct_helper_hsize,
						  &nf_ct_helper_vmalloc, 0);
	if (!nf_ct_helper_hash)
		return -ENOMEM;

	err = nf_ct_extend_register(&helper_extend);
	if (err < 0)
		goto err1;

	return 0;

err1:
	nf_ct_free_hashtable(nf_ct_helper_hash, nf_ct_helper_vmalloc,
			     nf_ct_helper_hsize);
	return err;
}