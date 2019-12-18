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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {struct label* v_label; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,struct label*,struct label*) ; 
 struct label* mac_vnode_label_alloc () ; 
 int /*<<< orphan*/  mac_vnode_label_free (struct label*) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_label_update ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

void
mac_vnode_label_update(vfs_context_t ctx, struct vnode *vp, struct label *newlabel)
{
	kauth_cred_t cred = vfs_context_ucred(ctx);
	struct label *tmpl = NULL;

	if (vp->v_label == NULL)
		tmpl = mac_vnode_label_alloc();

	vnode_lock(vp);

	/* recheck after lock */
	if (vp->v_label == NULL) {
		vp->v_label = tmpl;
		tmpl = NULL;
	}

	MAC_PERFORM(vnode_label_update, cred, vp, vp->v_label, newlabel);
	vnode_unlock(vp);

	if (tmpl != NULL)
		mac_vnode_label_free(tmpl);
}