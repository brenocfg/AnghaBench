#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  drv_data; int /*<<< orphan*/  drv_id; int /*<<< orphan*/  probed; } ;
typedef  TYPE_1__ in_dev_t ;
struct TYPE_5__ {int (* update_analog ) (int /*<<< orphan*/ ,int,int*) ;} ;

/* Variables and functions */
 TYPE_3__ DRV (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_dev (int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int*) ; 

int in_update_analog(int dev_id, int axis_id, int *result)
{
	in_dev_t *dev = get_dev(dev_id);

	if (dev == NULL || !dev->probed)
		return -1;

	return DRV(dev->drv_id).update_analog(dev->drv_data, axis_id, result);
}