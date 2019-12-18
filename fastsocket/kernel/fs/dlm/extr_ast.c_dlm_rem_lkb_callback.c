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
struct dlm_callback {int flags; int /*<<< orphan*/  mode; scalar_t__ seq; } ;
struct dlm_lkb {void* lkb_last_bast_time; struct dlm_callback lkb_last_bast; void* lkb_last_cast_time; struct dlm_callback lkb_last_cast; int /*<<< orphan*/  lkb_id; struct dlm_callback* lkb_callbacks; } ;

/* Variables and functions */
 int DLM_CALLBACKS_SIZE ; 
 int DLM_CB_BAST ; 
 int DLM_CB_CAST ; 
 int DLM_CB_SKIP ; 
 int ENOENT ; 
 scalar_t__ dlm_modes_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ktime_get () ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dlm_callback*,struct dlm_callback*,int) ; 
 int /*<<< orphan*/  memset (struct dlm_callback*,int /*<<< orphan*/ ,int) ; 

int dlm_rem_lkb_callback(struct dlm_ls *ls, struct dlm_lkb *lkb,
			 struct dlm_callback *cb, int *resid)
{
	int i;

	*resid = 0;

	if (!lkb->lkb_callbacks[0].seq)
		return -ENOENT;

	/* oldest undelivered cb is callbacks[0] */

	memcpy(cb, &lkb->lkb_callbacks[0], sizeof(struct dlm_callback));
	memset(&lkb->lkb_callbacks[0], 0, sizeof(struct dlm_callback));

	/* shift others down */

	for (i = 1; i < DLM_CALLBACKS_SIZE; i++) {
		if (!lkb->lkb_callbacks[i].seq)
			break;
		memcpy(&lkb->lkb_callbacks[i-1], &lkb->lkb_callbacks[i],
		       sizeof(struct dlm_callback));
		memset(&lkb->lkb_callbacks[i], 0, sizeof(struct dlm_callback));
		(*resid)++;
	}

	/* if cb is a bast, it should be skipped if the blocking mode is
	   compatible with the last granted mode */

	if ((cb->flags & DLM_CB_BAST) && lkb->lkb_last_cast.seq) {
		if (dlm_modes_compat(cb->mode, lkb->lkb_last_cast.mode)) {
			cb->flags |= DLM_CB_SKIP;

			log_debug(ls, "skip %x bast %llu mode %d "
				  "for cast %llu mode %d",
				  lkb->lkb_id,
				  (unsigned long long)cb->seq,
				  cb->mode,
				  (unsigned long long)lkb->lkb_last_cast.seq,
				  lkb->lkb_last_cast.mode);
			return 0;
		}
	}

	if (cb->flags & DLM_CB_CAST) {
		memcpy(&lkb->lkb_last_cast, cb, sizeof(struct dlm_callback));
		lkb->lkb_last_cast_time = ktime_get();
	}

	if (cb->flags & DLM_CB_BAST) {
		memcpy(&lkb->lkb_last_bast, cb, sizeof(struct dlm_callback));
		lkb->lkb_last_bast_time = ktime_get();
	}

	return 0;
}