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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int uint32_t ;
struct vnode_attr {int dummy; } ;

/* Variables and functions */
 int NOTE_ATTRIB ; 
 int NOTE_WRITE ; 
 int VNODE_EVENT_ATTRIB ; 
 int VNODE_EVENT_DELETE ; 
 int VNODE_EVENT_DIR_CREATED ; 
 int VNODE_EVENT_DIR_REMOVED ; 
 int VNODE_EVENT_EXTEND ; 
 int VNODE_EVENT_FILE_CREATED ; 
 int VNODE_EVENT_FILE_REMOVED ; 
 int VNODE_EVENT_LINK ; 
 int VNODE_EVENT_PERMS ; 
 int VNODE_EVENT_RENAME ; 
 int VNODE_EVENT_WRITE ; 
 int /*<<< orphan*/  create_fsevent_from_kevent (int /*<<< orphan*/ ,int,struct vnode_attr*) ; 
 int /*<<< orphan*/  lock_vnode_and_post (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vnode_isdir (int /*<<< orphan*/ ) ; 

int
vnode_notify(vnode_t vp, uint32_t events, struct vnode_attr *vap) 
{
	/* These are the same as the corresponding knotes, at least for now.  Cheating a little. */
	uint32_t knote_mask = (VNODE_EVENT_WRITE | VNODE_EVENT_DELETE | VNODE_EVENT_RENAME 
		| VNODE_EVENT_LINK | VNODE_EVENT_EXTEND | VNODE_EVENT_ATTRIB);
	uint32_t dir_contents_mask = (VNODE_EVENT_DIR_CREATED | VNODE_EVENT_FILE_CREATED 
			| VNODE_EVENT_DIR_REMOVED | VNODE_EVENT_FILE_REMOVED);
	uint32_t knote_events = (events & knote_mask);

	/* Permissions are not explicitly part of the kqueue model */
	if (events & VNODE_EVENT_PERMS) {
		knote_events |= NOTE_ATTRIB;
	} 

	/* Directory contents information just becomes NOTE_WRITE */
	if ((vnode_isdir(vp)) && (events & dir_contents_mask)) {
		knote_events |= NOTE_WRITE;
	}
	
	if (knote_events) {
		lock_vnode_and_post(vp, knote_events);
#if CONFIG_FSE
		if (vap != NULL) {
			create_fsevent_from_kevent(vp, events, vap);
		}
#else
		(void)vap;
#endif
	} 

	return 0;
}