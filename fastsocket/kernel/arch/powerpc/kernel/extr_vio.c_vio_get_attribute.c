#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct vio_dev {TYPE_2__ dev; } ;

/* Variables and functions */
 void const* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 

const void *vio_get_attribute(struct vio_dev *vdev, char *which, int *length)
{
	return of_get_property(vdev->dev.archdata.of_node, which, length);
}