#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct namecache {int dummy; } ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
struct TYPE_5__ {int /*<<< orphan*/  v_nc_generation; } ;
struct TYPE_4__ {scalar_t__ v_cred; scalar_t__ v_authorized_actions; int /*<<< orphan*/  v_ncchildren; int /*<<< orphan*/  v_nclinks; TYPE_3__* v_parent; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ *) ; 
 struct namecache* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 scalar_t__ NOCRED ; 
 TYPE_3__* NULLVP ; 
 struct namecache* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_delete (struct namecache*,int) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 

void
cache_purge(vnode_t vp)
{
        struct namecache *ncp;
	kauth_cred_t tcred = NULL;

	if ((LIST_FIRST(&vp->v_nclinks) == NULL) && 
			(TAILQ_FIRST(&vp->v_ncchildren) == NULL) &&
			(vp->v_cred == NOCRED) &&
			(vp->v_parent == NULLVP))
	        return;

	NAME_CACHE_LOCK();

	if (vp->v_parent)
	        vp->v_parent->v_nc_generation++;

	while ( (ncp = LIST_FIRST(&vp->v_nclinks)) )
	        cache_delete(ncp, 1);

	while ( (ncp = TAILQ_FIRST(&vp->v_ncchildren)) )
	        cache_delete(ncp, 1);

	/*
	 * Use a temp variable to avoid kauth_cred_unref() while NAME_CACHE_LOCK is held
	 */
	tcred = vp->v_cred;
	vp->v_cred = NOCRED;
	vp->v_authorized_actions = 0;

	NAME_CACHE_UNLOCK();

	if (IS_VALID_CRED(tcred))
	        kauth_cred_unref(&tcred);
}