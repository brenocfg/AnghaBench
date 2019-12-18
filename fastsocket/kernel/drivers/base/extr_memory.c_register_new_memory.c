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
struct mem_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOTPLUG ; 
 int /*<<< orphan*/  MEM_OFFLINE ; 
 int add_memory_section (int,struct mem_section*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int register_new_memory(int nid, struct mem_section *section)
{
	return add_memory_section(nid, section, MEM_OFFLINE, HOTPLUG);
}