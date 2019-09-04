#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
struct TYPE_3__ {int v_type; int v_specflags; } ;

/* Variables and functions */
 int SI_ALIASED ; 
 int VBLK ; 
 int VCHR ; 

int
vnode_isaliased(vnode_t vp)
{	
	enum vtype vt = vp->v_type;
	if (!((vt == VCHR) || (vt == VBLK))) {
		return 0;
	} else {
		return (vp->v_specflags & SI_ALIASED);
	}
}