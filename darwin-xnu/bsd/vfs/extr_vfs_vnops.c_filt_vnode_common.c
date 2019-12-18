#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
struct knote {int kn_flags; int kn_filter; long kn_sfflags; long kn_fflags; int /*<<< orphan*/  kn_data; TYPE_2__* kn_fp; } ;
struct TYPE_9__ {int /*<<< orphan*/  v_lock; } ;
struct TYPE_8__ {TYPE_1__* f_fglob; } ;
struct TYPE_7__ {int /*<<< orphan*/  fg_offset; } ;

/* Variables and functions */
#define  EVFILT_READ 130 
#define  EVFILT_VNODE 129 
#define  EVFILT_WRITE 128 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int EV_POLL ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 long NOTE_REVOKE ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_readable_data_count (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_writable_space_count (TYPE_3__*) ; 

__attribute__((used)) static int
filt_vnode_common(struct knote *kn, vnode_t vp, long hint)
{
	int activate = 0;

	lck_mtx_assert(&vp->v_lock, LCK_MTX_ASSERT_OWNED);

	/* Special handling for vnodes that are in recycle or already gone */
	if (NOTE_REVOKE == hint) {
		kn->kn_flags |= (EV_EOF | EV_ONESHOT);
		activate = 1;

		if ((kn->kn_filter == EVFILT_VNODE) && (kn->kn_sfflags & NOTE_REVOKE)) {
			kn->kn_fflags |= NOTE_REVOKE;
		}
	} else {
		switch(kn->kn_filter) {
			case EVFILT_READ:
				kn->kn_data = vnode_readable_data_count(vp, kn->kn_fp->f_fglob->fg_offset, (kn->kn_flags & EV_POLL));

				if (kn->kn_data != 0) {
					activate = 1;
				}
				break;
			case EVFILT_WRITE: 
				kn->kn_data = vnode_writable_space_count(vp);

				if (kn->kn_data != 0) {
					activate = 1;
				}
				break;
			case EVFILT_VNODE:
				/* Check events this note matches against the hint */
				if (kn->kn_sfflags & hint) {
					kn->kn_fflags |= hint; /* Set which event occurred */
				}
				if (kn->kn_fflags != 0) {
					activate = 1;
				}
				break;
			default:
				panic("Invalid knote filter on a vnode!\n");
		}
	}
	return (activate);
}