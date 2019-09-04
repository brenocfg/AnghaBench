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
struct uio {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int cluster_write_ext (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
cluster_write(vnode_t vp, struct uio *uio, off_t oldEOF, off_t newEOF, off_t headOff, off_t tailOff, int xflags)
{
        return cluster_write_ext(vp, uio, oldEOF, newEOF, headOff, tailOff, xflags, NULL, NULL);
}