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
struct vnode {TYPE_1__* v_ubcinfo; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_2__ {int /*<<< orphan*/  ui_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOCRED ; 
 scalar_t__ UBCINFOEXISTS (struct vnode*) ; 

kauth_cred_t
ubc_getcred(struct vnode *vp)
{
        if (UBCINFOEXISTS(vp))
	        return (vp->v_ubcinfo->ui_ucred);

	return (NOCRED);
}