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
 int /*<<< orphan*/  file_lck_attr ; 
 int /*<<< orphan*/  file_lck_grp ; 
 int /*<<< orphan*/  file_lck_grp_attr ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uipc_lock ; 

void
file_lock_init(void)
{
	/* allocate file lock group attribute and group */
	file_lck_grp_attr= lck_grp_attr_alloc_init();

	file_lck_grp = lck_grp_alloc_init("file",  file_lck_grp_attr);

	/* Allocate file lock attribute */
	file_lck_attr = lck_attr_alloc_init();

	uipc_lock = lck_mtx_alloc_init(file_lck_grp, file_lck_attr);
}