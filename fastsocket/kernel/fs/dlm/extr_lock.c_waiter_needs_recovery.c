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
struct dlm_ls {int dummy; } ;
struct dlm_lkb {scalar_t__ lkb_nodeid; int /*<<< orphan*/  lkb_resource; } ;

/* Variables and functions */
 scalar_t__ dlm_dir_nodeid (int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_is_removed (struct dlm_ls*,scalar_t__) ; 
 int /*<<< orphan*/  dlm_no_directory (struct dlm_ls*) ; 

__attribute__((used)) static int waiter_needs_recovery(struct dlm_ls *ls, struct dlm_lkb *lkb)
{
	if (dlm_is_removed(ls, lkb->lkb_nodeid))
		return 1;

	if (!dlm_no_directory(ls))
		return 0;

	if (dlm_dir_nodeid(lkb->lkb_resource) != lkb->lkb_nodeid)
		return 1;

	return 0;
}