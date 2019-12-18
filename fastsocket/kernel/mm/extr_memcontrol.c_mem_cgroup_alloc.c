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
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 struct mem_cgroup* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mem_cgroup_size () ; 
 int /*<<< orphan*/  memset (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 struct mem_cgroup* vmalloc (int) ; 

__attribute__((used)) static struct mem_cgroup *mem_cgroup_alloc(void)
{
	struct mem_cgroup *mem;
	int size = mem_cgroup_size();

	if (size < PAGE_SIZE)
		mem = kmalloc(size, GFP_KERNEL);
	else
		mem = vmalloc(size);

	if (mem)
		memset(mem, 0, size);
	return mem;
}