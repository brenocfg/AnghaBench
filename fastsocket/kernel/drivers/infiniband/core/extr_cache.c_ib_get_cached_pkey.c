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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ib_pkey_cache {int table_len; TYPE_1__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct ib_pkey_cache** pkey_cache; } ;
struct ib_device {TYPE_2__ cache; } ;
struct TYPE_3__ {int index; int pkey; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ end_port (struct ib_device*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ start_port (struct ib_device*) ; 

int ib_get_cached_pkey(struct ib_device *device,
		       u8                port_num,
		       int               index,
		       u16              *pkey)
{
	struct ib_pkey_cache *cache;
	unsigned long flags;
	int i, ret = 0;

	if (port_num < start_port(device) || port_num > end_port(device))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);

	cache = device->cache.pkey_cache[port_num - start_port(device)];

	if (index < 0 || index >= cache->table_len) {
		ret = -EINVAL;
		goto out_unlock;
	}

	for (i = 0; i < cache->table_len; ++i)
		if (cache->entry[i].index == index)
			break;

	if (i < cache->table_len)
		*pkey = cache->entry[i].pkey;
	else
		*pkey = 0x0000;

out_unlock:
	read_unlock_irqrestore(&device->cache.lock, flags);
	return ret;
}