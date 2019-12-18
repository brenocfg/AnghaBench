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
typedef  int uint64_t ;
struct vnode {scalar_t__ v_type; int /*<<< orphan*/  v_flag; TYPE_1__* v_mount; } ;
struct timespec {scalar_t__ tv_nsec; void* tv_sec; } ;
typedef  size_t nspace_type_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/ * handler_proc; } ;
struct TYPE_5__ {int op; int flags; int refcount; int token; int /*<<< orphan*/ * arg; struct vnode* vp; int /*<<< orphan*/  vid; } ;
struct TYPE_4__ {int mnt_kern_flag; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int MAX_NSPACE_ITEMS ; 
 int MNTK_VIRTUALDEV ; 
 int NAMESPACE_HANDLER_SNAPSHOT_EVENT ; 
 int NSPACE_ITEM_CANCELLED ; 
 int NSPACE_ITEM_DONE ; 
 int NSPACE_ITEM_NEW ; 
 int NSPACE_ITEM_RESET_TIMER ; 
 int NSPACE_ITEM_SNAPSHOT_EVENT ; 
 void* NSPACE_REARM_NO_ARG ; 
 int PCATCH ; 
 int PVFS ; 
 scalar_t__ VDIR ; 
 scalar_t__ VLNK ; 
 int /*<<< orphan*/  VNEEDSSNAPSHOT ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  nspace_allow_virtual_devs ; 
 int /*<<< orphan*/  nspace_handler_lock ; 
 void* nspace_handler_timeout ; 
 TYPE_3__* nspace_handlers ; 
 scalar_t__ nspace_is_special_process (int /*<<< orphan*/ ) ; 
 int nspace_item_flags_for_type (size_t) ; 
 int /*<<< orphan*/  nspace_item_idx ; 
 TYPE_2__* nspace_items ; 
 int /*<<< orphan*/  nspace_token_id ; 
 size_t nspace_type_for_op (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_vid (struct vnode*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
resolve_nspace_item_ext(struct vnode *vp, uint64_t op, void *arg)
{
	int i, error, keep_waiting;
	struct timespec ts;
	nspace_type_t nspace_type = nspace_type_for_op(op);

	// only allow namespace events on regular files, directories and symlinks.
	if (vp->v_type != VREG && vp->v_type != VDIR && vp->v_type != VLNK) {
		return 0;
	}

	//
	// if this is a snapshot event and the vnode is on a
	// disk image just pretend nothing happened since any
	// change to the disk image will cause the disk image
	// itself to get backed up and this avoids multi-way
	// deadlocks between the snapshot handler and the ever
	// popular diskimages-helper process.  the variable
	// nspace_allow_virtual_devs allows this behavior to
	// be overridden (for use by the Mobile TimeMachine
	// testing infrastructure which uses disk images)
	//
	if (   (op & NAMESPACE_HANDLER_SNAPSHOT_EVENT)
	    && (vp->v_mount != NULL)
	    && (vp->v_mount->mnt_kern_flag & MNTK_VIRTUALDEV)
	    && !nspace_allow_virtual_devs) {

		return 0;
	}

	// if (thread_tid(current_thread()) == namespace_handler_tid) {
	if (nspace_handlers[nspace_type].handler_proc == NULL) {
		return 0;
	}

	if (nspace_is_special_process(current_proc())) {
		return EDEADLK;
	}

	lck_mtx_lock(&nspace_handler_lock);

retry:
	for(i=0; i < MAX_NSPACE_ITEMS; i++) {
		if (vp == nspace_items[i].vp && op == nspace_items[i].op) {
			break;
		}
	}

	if (i >= MAX_NSPACE_ITEMS) {
		for(i=0; i < MAX_NSPACE_ITEMS; i++) {
			if (nspace_items[i].flags == 0) {
				break;
			}
		}
	} else {
		nspace_items[i].refcount++;
	}

	if (i >= MAX_NSPACE_ITEMS) {
		ts.tv_sec = nspace_handler_timeout;
		ts.tv_nsec = 0;

		error = msleep((caddr_t)&nspace_token_id, &nspace_handler_lock, PVFS|PCATCH, "nspace-no-space", &ts);
		if (error == 0) {
			// an entry got free'd up, go see if we can get a slot
			goto retry;
		} else {
			lck_mtx_unlock(&nspace_handler_lock);
			return error;
		}
	}

	//
	// if it didn't already exist, add it.  if it did exist
	// we'll get woken up when someone does a wakeup() on
	// the slot in the nspace_items table.
	//
	if (vp != nspace_items[i].vp) {
		nspace_items[i].vp = vp;
		nspace_items[i].arg = (arg == NSPACE_REARM_NO_ARG) ? NULL : arg;  // arg is {NULL, true, uio *} - only pass uio thru to the user
		nspace_items[i].op = op;
		nspace_items[i].vid = vnode_vid(vp);
		nspace_items[i].flags = NSPACE_ITEM_NEW;
		nspace_items[i].flags |= nspace_item_flags_for_type(nspace_type);
		if (nspace_items[i].flags & NSPACE_ITEM_SNAPSHOT_EVENT) {
			if (arg) {
				vnode_lock_spin(vp);
				vp->v_flag |= VNEEDSSNAPSHOT;
				vnode_unlock(vp);
			}
		}

		nspace_items[i].token = 0;
		nspace_items[i].refcount = 1;

		wakeup((caddr_t)&nspace_item_idx);
	}

	//
	// Now go to sleep until the handler does a wakeup on this
	// slot in the nspace_items table (or we timeout).
	//
	keep_waiting = 1;
	while(keep_waiting) {
		ts.tv_sec = nspace_handler_timeout;
		ts.tv_nsec = 0;
		error = msleep((caddr_t)&(nspace_items[i].vp), &nspace_handler_lock, PVFS|PCATCH, "namespace-done", &ts);

		if (nspace_items[i].flags & NSPACE_ITEM_DONE) {
			error = 0;
		} else if (nspace_items[i].flags & NSPACE_ITEM_CANCELLED) {
			error = nspace_items[i].token;
		} else if (error == EWOULDBLOCK || error == ETIMEDOUT) {
			if (nspace_items[i].flags & NSPACE_ITEM_RESET_TIMER) {
				nspace_items[i].flags &= ~NSPACE_ITEM_RESET_TIMER;
				continue;
			} else {
				error = ETIMEDOUT;
			}
		} else if (error == 0) {
			// hmmm, why did we get woken up?
			printf("woken up for token %d but it's not done, cancelled or timedout and error == 0.\n",
			       nspace_items[i].token);
		}

		if (--nspace_items[i].refcount == 0) {
			nspace_items[i].vp = NULL;     // clear this so that no one will match on it again
			nspace_items[i].arg = NULL;
			nspace_items[i].token = 0;     // clear this so that the handler will not find it anymore
			nspace_items[i].flags = 0;     // this clears it for re-use
		}
		wakeup(&nspace_token_id);
		keep_waiting = 0;
	}

	lck_mtx_unlock(&nspace_handler_lock);

	return error;
}