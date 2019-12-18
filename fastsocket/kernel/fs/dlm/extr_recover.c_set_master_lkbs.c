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
struct dlm_rsb {int /*<<< orphan*/  res_nodeid; int /*<<< orphan*/  res_waitqueue; int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_grantqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_lock_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_master_lkbs(struct dlm_rsb *r)
{
	set_lock_master(&r->res_grantqueue, r->res_nodeid);
	set_lock_master(&r->res_convertqueue, r->res_nodeid);
	set_lock_master(&r->res_waitqueue, r->res_nodeid);
}