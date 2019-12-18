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
struct vxgedev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_LL_FULL_RESET ; 
 int /*<<< orphan*/  do_vxge_reset (struct vxgedev*,int /*<<< orphan*/ ) ; 

int vxge_reset(struct vxgedev *vdev)
{
	do_vxge_reset(vdev, VXGE_LL_FULL_RESET);
	return 0;
}