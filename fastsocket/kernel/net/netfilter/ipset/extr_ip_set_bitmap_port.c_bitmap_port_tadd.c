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
typedef  int u32 ;
typedef  size_t u16 ;
struct ip_set {struct bitmap_port* data; } ;
struct bitmap_port {unsigned long* members; } ;

/* Variables and functions */
 int IPSET_ERR_EXIST ; 
 int IPSET_FLAG_EXIST ; 
 unsigned long ip_set_timeout_set (int) ; 
 scalar_t__ ip_set_timeout_test (unsigned long) ; 

__attribute__((used)) static int
bitmap_port_tadd(struct ip_set *set, void *value, u32 timeout, u32 flags)
{
	struct bitmap_port *map = set->data;
	unsigned long *members = map->members;
	u16 id = *(u16 *)value;

	if (ip_set_timeout_test(members[id]) && !(flags & IPSET_FLAG_EXIST))
		return -IPSET_ERR_EXIST;

	members[id] = ip_set_timeout_set(timeout);

	return 0;
}