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
struct wahc {int /*<<< orphan*/  xfer_id_count; int /*<<< orphan*/  xfer_work; int /*<<< orphan*/  xfer_list_lock; int /*<<< orphan*/  xfer_delayed_list; int /*<<< orphan*/  xfer_list; int /*<<< orphan*/  dti_edc; int /*<<< orphan*/  notifs_queued; int /*<<< orphan*/  nep_edc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  edc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wa_rpipe_init (struct wahc*) ; 
 int /*<<< orphan*/  wa_urb_enqueue_run ; 

__attribute__((used)) static inline void wa_init(struct wahc *wa)
{
	edc_init(&wa->nep_edc);
	atomic_set(&wa->notifs_queued, 0);
	wa_rpipe_init(wa);
	edc_init(&wa->dti_edc);
	INIT_LIST_HEAD(&wa->xfer_list);
	INIT_LIST_HEAD(&wa->xfer_delayed_list);
	spin_lock_init(&wa->xfer_list_lock);
	INIT_WORK(&wa->xfer_work, wa_urb_enqueue_run);
	atomic_set(&wa->xfer_id_count, 1);
}