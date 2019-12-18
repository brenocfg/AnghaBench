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
struct TYPE_4__ {int key_count; int does_combos; int /*<<< orphan*/  drv_data; int /*<<< orphan*/  drv_id; int /*<<< orphan*/  probed; } ;
typedef  TYPE_1__ in_dev_t ;
struct TYPE_5__ {int (* get_config ) (int /*<<< orphan*/ ,int,int*) ;} ;

/* Variables and functions */
 TYPE_3__ DRV (int /*<<< orphan*/ ) ; 
#define  IN_CFG_BIND_COUNT 131 
#define  IN_CFG_BLOCKING 130 
#define  IN_CFG_DOES_COMBOS 129 
#define  IN_CFG_KEY_NAMES 128 
 TYPE_1__* get_dev (int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int*) ; 

int in_get_config(int dev_id, int what, void *val)
{
	int *ival = val;
	in_dev_t *dev;

	dev = get_dev(dev_id);
	if (dev == NULL || val == NULL)
		return -1;

	switch (what) {
	case IN_CFG_BIND_COUNT:
		*ival = dev->key_count;
		break;
	case IN_CFG_DOES_COMBOS:
		*ival = dev->does_combos;
		break;
	case IN_CFG_BLOCKING:
	case IN_CFG_KEY_NAMES:
		return -1; /* not implemented */
	default:
		if (!dev->probed)
			return -1;

		return DRV(dev->drv_id).get_config(dev->drv_data, what, ival);
	}

	return 0;
}