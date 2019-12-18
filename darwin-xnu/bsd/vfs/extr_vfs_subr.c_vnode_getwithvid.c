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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int VNODE_DRAINO ; 
 int VNODE_NODEAD ; 
 int VNODE_WITHID ; 
 int vget_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
vnode_getwithvid(vnode_t vp, uint32_t vid)
{
        return(vget_internal(vp, vid, ( VNODE_NODEAD | VNODE_WITHID | VNODE_DRAINO )));
}