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
struct dlm_ls {int ls_rsbtbl_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ dlm_locking_stopped (struct dlm_ls*) ; 
 int /*<<< orphan*/  shrink_bucket (struct dlm_ls*,int) ; 

void dlm_scan_rsbs(struct dlm_ls *ls)
{
	int i;

	for (i = 0; i < ls->ls_rsbtbl_size; i++) {
		shrink_bucket(ls, i);
		if (dlm_locking_stopped(ls))
			break;
		cond_resched();
	}
}