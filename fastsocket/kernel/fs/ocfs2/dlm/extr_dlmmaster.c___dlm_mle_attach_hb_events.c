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
struct dlm_master_list_entry {int /*<<< orphan*/  hb_events; } ;
struct dlm_ctxt {int /*<<< orphan*/  mle_hb_events; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __dlm_mle_attach_hb_events(struct dlm_ctxt *dlm,
					      struct dlm_master_list_entry *mle)
{
	assert_spin_locked(&dlm->spinlock);

	list_add_tail(&mle->hb_events, &dlm->mle_hb_events);
}