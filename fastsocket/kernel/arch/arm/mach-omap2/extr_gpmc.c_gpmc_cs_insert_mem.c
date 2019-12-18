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
struct resource {unsigned long start; unsigned long end; } ;

/* Variables and functions */
 struct resource* gpmc_cs_mem ; 
 unsigned long gpmc_mem_align (unsigned long) ; 
 int /*<<< orphan*/  gpmc_mem_lock ; 
 int /*<<< orphan*/  gpmc_mem_root ; 
 int request_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpmc_cs_insert_mem(int cs, unsigned long base, unsigned long size)
{
	struct resource	*res = &gpmc_cs_mem[cs];
	int r;

	size = gpmc_mem_align(size);
	spin_lock(&gpmc_mem_lock);
	res->start = base;
	res->end = base + size - 1;
	r = request_resource(&gpmc_mem_root, res);
	spin_unlock(&gpmc_mem_lock);

	return r;
}