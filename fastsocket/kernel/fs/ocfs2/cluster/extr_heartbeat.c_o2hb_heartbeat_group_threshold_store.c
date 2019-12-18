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
struct o2hb_heartbeat_group {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  o2hb_dead_threshold_set (unsigned int) ; 
 unsigned long simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static ssize_t o2hb_heartbeat_group_threshold_store(struct o2hb_heartbeat_group *group,
						    const char *page,
						    size_t count)
{
	unsigned long tmp;
	char *p = (char *)page;

	tmp = simple_strtoul(p, &p, 10);
	if (!p || (*p && (*p != '\n')))
                return -EINVAL;

	/* this will validate ranges for us. */
	o2hb_dead_threshold_set((unsigned int) tmp);

	return count;
}