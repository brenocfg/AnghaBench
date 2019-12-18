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

/* Variables and functions */
 int /*<<< orphan*/  vnode_getalways (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_rele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vnode_get_and_drop_always(vnode_t vp) 
{
	vnode_getalways(vp);
	vnode_rele(vp);
	vnode_put(vp);
}