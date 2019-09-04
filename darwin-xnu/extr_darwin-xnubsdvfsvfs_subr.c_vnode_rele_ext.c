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
 int /*<<< orphan*/  vnode_rele_internal (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
vnode_rele_ext(vnode_t vp, int fmode, int dont_reenter)
{
        vnode_rele_internal(vp, fmode, dont_reenter, 0);
}