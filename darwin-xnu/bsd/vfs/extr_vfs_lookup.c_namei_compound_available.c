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
struct nameidata {int ni_flag; } ;

/* Variables and functions */
 int NAMEI_COMPOUNDOPEN ; 
 int vnode_compound_open_available (int /*<<< orphan*/ ) ; 

int		
namei_compound_available(vnode_t dp, struct nameidata *ndp)
{
	if ((ndp->ni_flag & NAMEI_COMPOUNDOPEN) != 0) {
		return vnode_compound_open_available(dp);
	}

	return 0;
}