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
struct if_group {unsigned char const group; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char clear_group_from_set(const unsigned char groups, struct if_group *group)
{
	return (groups & ~group->group);
}