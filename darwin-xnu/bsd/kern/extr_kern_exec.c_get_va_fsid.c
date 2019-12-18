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
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode_attr {int /*<<< orphan*/  va_fsid; int /*<<< orphan*/  va_fsid64; } ;

/* Variables and functions */
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_fsid64 ; 

__attribute__((used)) static uint64_t get_va_fsid(struct vnode_attr *vap)
{
	if (VATTR_IS_SUPPORTED(vap, va_fsid64)) {
		return *(uint64_t *)&vap->va_fsid64;
	} else {
		return vap->va_fsid;
	}
}