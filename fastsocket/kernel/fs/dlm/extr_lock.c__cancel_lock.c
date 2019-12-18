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
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int do_cancel (struct dlm_rsb*,struct dlm_lkb*) ; 
 scalar_t__ is_remote (struct dlm_rsb*) ; 
 int send_cancel (struct dlm_rsb*,struct dlm_lkb*) ; 

__attribute__((used)) static int _cancel_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error;

	if (is_remote(r))
		/* receive_cancel() calls do_cancel() on remote node */
		error = send_cancel(r, lkb);
	else
		error = do_cancel(r, lkb);

	return error;
}