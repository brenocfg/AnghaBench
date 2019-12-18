#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  scalar_t__ uint32_t ;
struct doc_tombstone {char* t_lastop_filename; scalar_t__ t_lastop_item_vid; scalar_t__ t_lastop_fileid; TYPE_1__* t_lastop_item; scalar_t__ t_lastop_parent_vid; int /*<<< orphan*/ * t_lastop_parent; scalar_t__ t_lastop_document_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  v_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VL_TERMINATE ; 
 int vnode_get (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 scalar_t__ vnode_vid (TYPE_1__*) ; 

void
doc_tombstone_clear(struct doc_tombstone *ut, vnode_t *old_vpp)
{
	uint32_t old_id = ut->t_lastop_document_id;

	ut->t_lastop_document_id = 0;
	ut->t_lastop_parent = NULL;
	ut->t_lastop_parent_vid = 0;
	ut->t_lastop_filename[0] = '\0';

	//
	// If the lastop item is still the same and needs to be cleared,
	// clear it.  The following isn't ideal because the vnode might
	// have been recycled.
	//
	if (old_vpp) {
		*old_vpp = NULL;
		if (old_id && ut->t_lastop_item
			&& vnode_vid(ut->t_lastop_item) == ut->t_lastop_item_vid) {
			int res = vnode_get(ut->t_lastop_item);
			if (!res) {
				// Need to check vid again
				if (vnode_vid(ut->t_lastop_item) == ut->t_lastop_item_vid
					&& !ISSET(ut->t_lastop_item->v_lflag, VL_TERMINATE))
					*old_vpp = ut->t_lastop_item;
				else
					vnode_put(ut->t_lastop_item);
			}
		}
	}

	// last, clear these now that we're all done
	ut->t_lastop_item     = NULL;
	ut->t_lastop_fileid   = 0;
	ut->t_lastop_item_vid = 0;
}