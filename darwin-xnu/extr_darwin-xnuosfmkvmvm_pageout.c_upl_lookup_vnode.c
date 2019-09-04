#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* upl_t ;
struct vnode {int dummy; } ;
struct TYPE_5__ {TYPE_1__* map_object; } ;
struct TYPE_4__ {int /*<<< orphan*/  pager; int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 struct vnode* vnode_pager_lookup_vnode (int /*<<< orphan*/ ) ; 

struct vnode * upl_lookup_vnode(upl_t upl)
{
	if (!upl->map_object->internal)
		return vnode_pager_lookup_vnode(upl->map_object->pager);
	else
		return NULL;
}