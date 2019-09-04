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
typedef  int /*<<< orphan*/  mib ;
typedef  int /*<<< orphan*/  dss_precs ;
typedef  int /*<<< orphan*/  arena_ind ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MALLOCX_ARENA (unsigned int) ; 
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ have_dss ; 
 int /*<<< orphan*/  mallctl (char*,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctlbymib (size_t*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  mallctlnametomib (char*,size_t*,size_t*) ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 

void *
thd_start(void *arg)
{
	unsigned thread_ind = (unsigned)(uintptr_t)arg;
	unsigned arena_ind;
	void *p;
	size_t sz;

	sz = sizeof(arena_ind);
	assert_d_eq(mallctl("arenas.extend", &arena_ind, &sz, NULL, 0), 0,
	    "Error in arenas.extend");

	if (thread_ind % 4 != 3) {
		size_t mib[3];
		size_t miblen = sizeof(mib) / sizeof(size_t);
		const char *dss_precs[] = {"disabled", "primary", "secondary"};
		unsigned prec_ind = thread_ind %
		    (sizeof(dss_precs)/sizeof(char*));
		const char *dss = dss_precs[prec_ind];
		int expected_err = (have_dss || prec_ind == 0) ? 0 : EFAULT;
		assert_d_eq(mallctlnametomib("arena.0.dss", mib, &miblen), 0,
		    "Error in mallctlnametomib()");
		mib[1] = arena_ind;
		assert_d_eq(mallctlbymib(mib, miblen, NULL, NULL, (void *)&dss,
		    sizeof(const char *)), expected_err,
		    "Error in mallctlbymib()");
	}

	p = mallocx(1, MALLOCX_ARENA(arena_ind));
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	dallocx(p, 0);

	return (NULL);
}