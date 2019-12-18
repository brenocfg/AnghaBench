#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {scalar_t__ cb_expires; int /*<<< orphan*/  validate_lock; int /*<<< orphan*/  flags; scalar_t__ cb_promised; TYPE_1__ fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_BROKEN ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  AFS_VNODE_MODIFIED ; 
 int /*<<< orphan*/  AFS_VNODE_ZAP_DATA ; 
 int ESTALE ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_vnode_fetch_status (struct afs_vnode*,int /*<<< orphan*/ *,struct key*) ; 
 int /*<<< orphan*/  afs_zap_data (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int afs_validate(struct afs_vnode *vnode, struct key *key)
{
	int ret;

	_enter("{v={%x:%u} fl=%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, vnode->flags,
	       key_serial(key));

	if (vnode->cb_promised &&
	    !test_bit(AFS_VNODE_CB_BROKEN, &vnode->flags) &&
	    !test_bit(AFS_VNODE_MODIFIED, &vnode->flags) &&
	    !test_bit(AFS_VNODE_ZAP_DATA, &vnode->flags)) {
		if (vnode->cb_expires < get_seconds() + 10) {
			_debug("callback expired");
			set_bit(AFS_VNODE_CB_BROKEN, &vnode->flags);
		} else {
			goto valid;
		}
	}

	if (test_bit(AFS_VNODE_DELETED, &vnode->flags))
		goto valid;

	mutex_lock(&vnode->validate_lock);

	/* if the promise has expired, we need to check the server again to get
	 * a new promise - note that if the (parent) directory's metadata was
	 * changed then the security may be different and we may no longer have
	 * access */
	if (!vnode->cb_promised ||
	    test_bit(AFS_VNODE_CB_BROKEN, &vnode->flags)) {
		_debug("not promised");
		ret = afs_vnode_fetch_status(vnode, NULL, key);
		if (ret < 0)
			goto error_unlock;
		_debug("new promise [fl=%lx]", vnode->flags);
	}

	if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		_debug("file already deleted");
		ret = -ESTALE;
		goto error_unlock;
	}

	/* if the vnode's data version number changed then its contents are
	 * different */
	if (test_and_clear_bit(AFS_VNODE_ZAP_DATA, &vnode->flags))
		afs_zap_data(vnode);

	clear_bit(AFS_VNODE_MODIFIED, &vnode->flags);
	mutex_unlock(&vnode->validate_lock);
valid:
	_leave(" = 0");
	return 0;

error_unlock:
	mutex_unlock(&vnode->validate_lock);
	_leave(" = %d", ret);
	return ret;
}