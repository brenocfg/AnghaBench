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
 int EINVAL ; 
 int /*<<< orphan*/  present_section (struct mem_section*) ; 
 int remove_memory_block (int /*<<< orphan*/ ,struct mem_section*,int /*<<< orphan*/ ) ; 

int unregister_memory_section(struct mem_section *section)
{
	if (!present_section(section))
		return -EINVAL;

	return remove_memory_block(0, section, 0);
}