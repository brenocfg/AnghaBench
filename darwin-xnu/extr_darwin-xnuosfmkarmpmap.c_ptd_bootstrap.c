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
typedef  int /*<<< orphan*/  pt_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ptd_free_count ; 
 int /*<<< orphan*/ * ptd_free_list ; 
 int /*<<< orphan*/  ptd_free_list_lock ; 
 int /*<<< orphan*/  ptd_preboot ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptd_bootstrap(
	pt_desc_t *ptdp,
	unsigned int ptd_cnt)
{
	simple_lock_init(&ptd_free_list_lock, 0);
	while (ptd_cnt != 0) {
		(*(void **)ptdp) = (void *)ptd_free_list;
		ptd_free_list = ptdp;
		ptdp++;
		ptd_cnt--;
		ptd_free_count++;
	}
	ptd_preboot = FALSE;
}