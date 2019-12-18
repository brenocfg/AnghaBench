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
struct dlm_message {int dummy; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _receive_message (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  dlm_add_requestqueue (struct dlm_ls*,int,struct dlm_message*) ; 
 scalar_t__ dlm_locking_stopped (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_wait_requestqueue (struct dlm_ls*) ; 

__attribute__((used)) static void dlm_receive_message(struct dlm_ls *ls, struct dlm_message *ms,
				int nodeid)
{
	if (dlm_locking_stopped(ls)) {
		dlm_add_requestqueue(ls, nodeid, ms);
	} else {
		dlm_wait_requestqueue(ls);
		_receive_message(ls, ms);
	}
}