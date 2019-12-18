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
struct dlm_rsb {int res_nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSB_NEW_MASTER ; 
 int /*<<< orphan*/  RSB_NEW_MASTER2 ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_master_lkbs (struct dlm_rsb*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 

__attribute__((used)) static void set_new_master(struct dlm_rsb *r, int nodeid)
{
	lock_rsb(r);
	r->res_nodeid = nodeid;
	set_master_lkbs(r);
	rsb_set_flag(r, RSB_NEW_MASTER);
	rsb_set_flag(r, RSB_NEW_MASTER2);
	unlock_rsb(r);
}