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
 int /*<<< orphan*/  helper_extend ; 
 int /*<<< orphan*/  nf_ct_extend_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_free_hashtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_helper_hash ; 
 int /*<<< orphan*/  nf_ct_helper_hsize ; 
 int /*<<< orphan*/  nf_ct_helper_vmalloc ; 

void nf_conntrack_helper_fini(void)
{
	nf_ct_extend_unregister(&helper_extend);
	nf_ct_free_hashtable(nf_ct_helper_hash, nf_ct_helper_vmalloc,
			     nf_ct_helper_hsize);
}