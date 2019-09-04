#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mcache_obj_t ;
struct TYPE_3__ {scalar_t__ mca_contents; } ;
typedef  TYPE_1__ mcache_audit_t ;
struct TYPE_4__ {TYPE_1__** cl_audit; } ;

/* Variables and functions */
 unsigned int MTOPG (void*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 unsigned int maxclaudit ; 
 int /*<<< orphan*/  mcache_audit_cache ; 
 int /*<<< orphan*/  mcache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mcache_free_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcl_audit_con_cache ; 
 TYPE_2__* mclaudit ; 

__attribute__((used)) static void
mcl_audit_free(void *buf, unsigned int num)
{
	unsigned int i, ix;
	mcache_audit_t *mca, *mca_list;

	ix = MTOPG(buf);
	VERIFY(ix < maxclaudit);

	if (mclaudit[ix].cl_audit[0] != NULL) {
		mca_list = mclaudit[ix].cl_audit[0];
		for (i = 0; i < num; i++) {
			mca = mclaudit[ix].cl_audit[i];
			mclaudit[ix].cl_audit[i] = NULL;
			if (mca->mca_contents)
				mcache_free(mcl_audit_con_cache,
				    mca->mca_contents);
		}
		mcache_free_ext(mcache_audit_cache,
		    (mcache_obj_t *)mca_list);
	}
}