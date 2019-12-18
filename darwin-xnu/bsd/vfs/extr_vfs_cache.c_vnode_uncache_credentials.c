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
 int /*<<< orphan*/  KAUTH_INVALIDATE_CACHED_RIGHTS ; 
 int /*<<< orphan*/  vnode_uncache_authorized_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnode_uncache_credentials(vnode_t vp)
{
        vnode_uncache_authorized_action(vp, KAUTH_INVALIDATE_CACHED_RIGHTS);
}