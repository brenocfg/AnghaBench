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
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_support_available ; 
 int /*<<< orphan*/  hv_support_lck_grp ; 
 int /*<<< orphan*/  hv_support_lck_mtx ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_hv_support () ; 

void
hv_support_init(void) {
#if defined(__x86_64__) && CONFIG_VMX
	hv_support_available = vmx_hv_support();
#endif

	hv_support_lck_grp = lck_grp_alloc_init("hv_support", LCK_GRP_ATTR_NULL);
	assert(hv_support_lck_grp);

	hv_support_lck_mtx = lck_mtx_alloc_init(hv_support_lck_grp, LCK_ATTR_NULL);
	assert(hv_support_lck_mtx);
}