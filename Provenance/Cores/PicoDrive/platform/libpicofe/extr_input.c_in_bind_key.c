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
struct TYPE_4__ {int key_count; int* binds; int /*<<< orphan*/  drv_data; int /*<<< orphan*/  drv_id; } ;
typedef  TYPE_1__ in_dev_t ;
struct TYPE_5__ {int (* clean_binds ) (int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
 TYPE_3__ DRV (int /*<<< orphan*/ ) ; 
 int IN_BINDTYPE_COUNT ; 
 size_t IN_BIND_OFFS (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_1__* get_dev (int) ; 
 int* in_alloc_binds (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int*,int*) ; 

int in_bind_key(int dev_id, int keycode, int mask, int bind_type, int force_unbind)
{
	int ret, count;
	in_dev_t *dev;

	dev = get_dev(dev_id);
	if (dev == NULL || bind_type >= IN_BINDTYPE_COUNT)
		return -1;

	count = dev->key_count;

	if (dev->binds == NULL) {
		if (force_unbind)
			return 0;
		dev->binds = in_alloc_binds(dev->drv_id, count);
		if (dev->binds == NULL)
			return -1;
	}

	if (keycode < 0 || keycode >= count)
		return -1;
	
	if (force_unbind)
		dev->binds[IN_BIND_OFFS(keycode, bind_type)] &= ~mask;
	else
		dev->binds[IN_BIND_OFFS(keycode, bind_type)] ^=  mask;
	
	ret = DRV(dev->drv_id).clean_binds(dev->drv_data, dev->binds,
				dev->binds + count * IN_BINDTYPE_COUNT);
	if (ret == 0) {
		free(dev->binds);
		dev->binds = NULL;
	}

	return 0;
}