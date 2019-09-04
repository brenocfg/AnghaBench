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
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int /*<<< orphan*/  lck_grp_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  fpxlock ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fpxlog_init(void)
{
	lck_grp_attr_t *lck_grp_attr = lck_grp_attr_alloc_init();
	lck_grp_t *lck_grp = lck_grp_alloc_init("fpx", lck_grp_attr);
	lck_mtx_init(&fpxlock, lck_grp, LCK_ATTR_NULL);
}