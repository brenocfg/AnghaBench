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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  ui_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 

off_t
ubc_getsize(struct vnode *vp)
{
	/* people depend on the side effect of this working this way
	 * as they call this for directory 
	 */
	if (!UBCINFOEXISTS(vp))
		return ((off_t)0);
	return (vp->v_ubcinfo->ui_size);
}