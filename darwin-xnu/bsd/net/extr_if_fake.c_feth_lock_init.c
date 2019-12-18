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

/* Variables and functions */
 int /*<<< orphan*/  feth_lck_mtx ; 
 int /*<<< orphan*/ * my_lck_grp_alloc_init (char*) ; 
 int /*<<< orphan*/  my_lck_mtx_alloc_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
feth_lock_init(void)
{
	lck_grp_t *		feth_lck_grp;

	feth_lck_grp = my_lck_grp_alloc_init("fake");
	feth_lck_mtx = my_lck_mtx_alloc_init(feth_lck_grp);
}