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
struct protosw {int dummy; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_mtx ; 
 int /*<<< orphan*/  raw_mtx_attr ; 
 int /*<<< orphan*/  raw_mtx_grp ; 
 int /*<<< orphan*/  raw_mtx_grp_attr ; 
 int /*<<< orphan*/  rawcb_list ; 

void
raw_init(struct protosw *pp, struct domain *dp)
{
#pragma unused(pp, dp)
	static int raw_initialized = 0;

	/* This is called by key_init as well, so do it only once */
	if (!raw_initialized) {
		raw_initialized = 1;

		raw_mtx_grp_attr = lck_grp_attr_alloc_init();
		raw_mtx_grp = lck_grp_alloc_init("rawcb", raw_mtx_grp_attr);
		raw_mtx_attr = lck_attr_alloc_init();

		lck_mtx_init(raw_mtx, raw_mtx_grp, raw_mtx_attr);
		LIST_INIT(&rawcb_list);
	}
}