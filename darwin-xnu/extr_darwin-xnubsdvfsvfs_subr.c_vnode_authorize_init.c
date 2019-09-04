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

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_SCOPE_VNODE ; 
 int /*<<< orphan*/  kauth_register_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_authorize_callback ; 
 int /*<<< orphan*/  vnode_scope ; 

void
vnode_authorize_init(void)
{
	vnode_scope = kauth_register_scope(KAUTH_SCOPE_VNODE, vnode_authorize_callback, NULL);
}