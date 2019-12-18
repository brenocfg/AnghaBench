#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * td_iihash; int /*<<< orphan*/ * td_layouthash; int /*<<< orphan*/ * td_labels; int /*<<< orphan*/ * td_fwdlist; void* td_nextid; void* td_curvgen; void* td_curemark; } ;
typedef  TYPE_1__ tdata_t ;

/* Variables and functions */
 void* MAX (void*,void*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slist_merge (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdata_build_hashes_common (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdata_free (TYPE_1__*) ; 
 int /*<<< orphan*/  tdata_label_cmp ; 

void
tdata_merge(tdata_t *td1, tdata_t *td2)
{
	td1->td_curemark = MAX(td1->td_curemark, td2->td_curemark);
	td1->td_curvgen = MAX(td1->td_curvgen, td2->td_curvgen);
	td1->td_nextid = MAX(td1->td_nextid, td2->td_nextid);

	hash_merge(td1->td_iihash, td2->td_iihash);

	/* Add td2's type tree to the hashes */
	tdata_build_hashes_common(td1, td2->td_iihash);

	list_concat(&td1->td_fwdlist, td2->td_fwdlist);
	td2->td_fwdlist = NULL;

	slist_merge(&td1->td_labels, td2->td_labels,
	    tdata_label_cmp);
	td2->td_labels = NULL;

	/* free the td2 hashes (data is now part of td1) */

	hash_free(td2->td_layouthash, NULL, NULL);
	td2->td_layouthash = NULL;

	hash_free(td2->td_iihash, NULL, NULL);
	td2->td_iihash = NULL;

	tdata_free(td2);
}