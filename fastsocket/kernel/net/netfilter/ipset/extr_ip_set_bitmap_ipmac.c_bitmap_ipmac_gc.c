#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ipmac_telem {scalar_t__ match; int /*<<< orphan*/  timeout; } ;
struct ip_set {int /*<<< orphan*/  lock; struct bitmap_ipmac* data; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct bitmap_ipmac {scalar_t__ last_ip; scalar_t__ first_ip; TYPE_1__ gc; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int HZ ; 
 int IPSET_GC_PERIOD (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_EMPTY ; 
 scalar_t__ MAC_FILLED ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct ipmac_telem* bitmap_ipmac_elem (struct bitmap_ipmac*,scalar_t__) ; 
 scalar_t__ ip_set_timeout_expired (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bitmap_ipmac_gc(unsigned long ul_set)
{
	struct ip_set *set = (struct ip_set *) ul_set;
	struct bitmap_ipmac *map = set->data;
	struct ipmac_telem *elem;
	u32 id, last = map->last_ip - map->first_ip;

	/* We run parallel with other readers (test element)
	 * but adding/deleting new entries is locked out */
	read_lock_bh(&set->lock);
	for (id = 0; id <= last; id++) {
		elem = bitmap_ipmac_elem(map, id);
		if (elem->match == MAC_FILLED &&
		    ip_set_timeout_expired(elem->timeout))
			elem->match = MAC_EMPTY;
	}
	read_unlock_bh(&set->lock);

	map->gc.expires = jiffies + IPSET_GC_PERIOD(map->timeout) * HZ;
	add_timer(&map->gc);
}