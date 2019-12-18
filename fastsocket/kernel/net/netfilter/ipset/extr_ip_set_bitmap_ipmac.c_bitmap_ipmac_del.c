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
typedef  int /*<<< orphan*/  u32 ;
struct ipmac_elem {scalar_t__ match; } ;
struct ipmac {int /*<<< orphan*/  id; } ;
struct ip_set {struct bitmap_ipmac* data; } ;
struct bitmap_ipmac {int dummy; } ;

/* Variables and functions */
 int IPSET_ERR_EXIST ; 
 scalar_t__ MAC_EMPTY ; 
 struct ipmac_elem* bitmap_ipmac_elem (struct bitmap_ipmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bitmap_ipmac_del(struct ip_set *set, void *value, u32 timeout, u32 flags)
{
	struct bitmap_ipmac *map = set->data;
	const struct ipmac *data = value;
	struct ipmac_elem *elem = bitmap_ipmac_elem(map, data->id);

	if (elem->match == MAC_EMPTY)
		return -IPSET_ERR_EXIST;

	elem->match = MAC_EMPTY;

	return 0;
}