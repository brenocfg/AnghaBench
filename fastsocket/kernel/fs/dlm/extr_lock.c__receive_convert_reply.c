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
struct dlm_message {int dummy; } ;
struct dlm_lkb {struct dlm_rsb* lkb_resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  __receive_convert_reply (struct dlm_rsb*,struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  hold_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  lock_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  put_rsb (struct dlm_rsb*) ; 
 int remove_from_waiters_ms (struct dlm_lkb*,struct dlm_message*) ; 
 int /*<<< orphan*/  unlock_rsb (struct dlm_rsb*) ; 
 int validate_message (struct dlm_lkb*,struct dlm_message*) ; 

__attribute__((used)) static void _receive_convert_reply(struct dlm_lkb *lkb, struct dlm_message *ms)
{
	struct dlm_rsb *r = lkb->lkb_resource;
	int error;

	hold_rsb(r);
	lock_rsb(r);

	error = validate_message(lkb, ms);
	if (error)
		goto out;

	/* stub reply can happen with waiters_mutex held */
	error = remove_from_waiters_ms(lkb, ms);
	if (error)
		goto out;

	__receive_convert_reply(r, lkb, ms);
 out:
	unlock_rsb(r);
	put_rsb(r);
}