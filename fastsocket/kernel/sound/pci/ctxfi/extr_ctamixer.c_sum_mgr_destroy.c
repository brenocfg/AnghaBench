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
struct sum_mgr {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sum_mgr*) ; 
 int /*<<< orphan*/  rsc_mgr_uninit (int /*<<< orphan*/ *) ; 

int sum_mgr_destroy(struct sum_mgr *sum_mgr)
{
	rsc_mgr_uninit(&sum_mgr->mgr);
	kfree(sum_mgr);
	return 0;
}