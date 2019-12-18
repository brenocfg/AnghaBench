#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_status; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; scalar_t__ seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_status; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; scalar_t__ seq; } ;
struct dlm_lkb {TYPE_3__* lkb_callbacks; int /*<<< orphan*/  lkb_id; TYPE_2__ lkb_last_cast; TYPE_1__ lkb_last_bast; } ;
struct TYPE_6__ {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_status; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; scalar_t__ seq; } ;

/* Variables and functions */
 int DLM_CALLBACKS_SIZE ; 
 int /*<<< orphan*/  log_print (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_dump_lkb_callbacks(struct dlm_lkb *lkb)
{
	int i;

	log_print("last_bast %x %llu flags %x mode %d sb %d %x",
		  lkb->lkb_id,
		  (unsigned long long)lkb->lkb_last_bast.seq,
		  lkb->lkb_last_bast.flags,
		  lkb->lkb_last_bast.mode,
		  lkb->lkb_last_bast.sb_status,
		  lkb->lkb_last_bast.sb_flags);

	log_print("last_cast %x %llu flags %x mode %d sb %d %x",
		  lkb->lkb_id,
		  (unsigned long long)lkb->lkb_last_cast.seq,
		  lkb->lkb_last_cast.flags,
		  lkb->lkb_last_cast.mode,
		  lkb->lkb_last_cast.sb_status,
		  lkb->lkb_last_cast.sb_flags);

	for (i = 0; i < DLM_CALLBACKS_SIZE; i++) {
		log_print("cb %x %llu flags %x mode %d sb %d %x",
			  lkb->lkb_id,
			  (unsigned long long)lkb->lkb_callbacks[i].seq,
			  lkb->lkb_callbacks[i].flags,
			  lkb->lkb_callbacks[i].mode,
			  lkb->lkb_callbacks[i].sb_status,
			  lkb->lkb_callbacks[i].sb_flags);
	}
}