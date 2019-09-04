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
 int cluster_read_ext (int /*<<< orphan*/ ,struct uio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
cluster_read(vnode_t vp, struct uio *uio, off_t filesize, int xflags)
{
        return cluster_read_ext(vp, uio, filesize, xflags, NULL, NULL);
}