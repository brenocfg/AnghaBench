#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
struct image_params {scalar_t__ ip_vp; scalar_t__ ip_arch_offset; } ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ p_textvp; scalar_t__ p_textoff; } ;

/* Variables and functions */
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 scalar_t__ vnode_getwithref (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 int vnode_ref (scalar_t__) ; 
 int /*<<< orphan*/  vnode_rele (scalar_t__) ; 

__attribute__((used)) static void
exec_resettextvp(proc_t p, struct image_params *imgp)
{
	vnode_t vp;
	off_t offset;
	vnode_t tvp  = p->p_textvp;
	int ret;

	vp = imgp->ip_vp;
	offset = imgp->ip_arch_offset;

	if (vp == NULLVP)
		panic("exec_resettextvp: expected valid vp");

	ret = vnode_ref(vp);
	proc_lock(p);
	if (ret == 0) {
		p->p_textvp = vp;
		p->p_textoff = offset;
	} else {
		p->p_textvp = NULLVP;	/* this is paranoia */
		p->p_textoff = 0;
	}
	proc_unlock(p);

	if ( tvp != NULLVP) {
		if (vnode_getwithref(tvp) == 0) {
			vnode_rele(tvp);
			vnode_put(tvp);
		}
	}	

}