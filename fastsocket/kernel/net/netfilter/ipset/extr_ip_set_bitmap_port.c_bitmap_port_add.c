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
typedef  int /*<<< orphan*/  u16 ;
struct ip_set {struct bitmap_port* data; } ;
struct bitmap_port {int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int IPSET_ERR_EXIST ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bitmap_port_add(struct ip_set *set, void *value, u32 timeout, u32 flags)
{
	struct bitmap_port *map = set->data;
	u16 id = *(u16 *)value;

	if (test_and_set_bit(id, map->members))
		return -IPSET_ERR_EXIST;

	return 0;
}