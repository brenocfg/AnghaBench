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

/* Variables and functions */
 unsigned long long MAX_PHYSMEM_BITS ; 
 int /*<<< orphan*/  ehca_create_busmap_callback ; 
 scalar_t__ ehca_mr_len ; 
 int walk_system_ram_range (int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ehca_create_busmap(void)
{
	int ret;

	ehca_mr_len = 0;
	ret = walk_system_ram_range(0, 1ULL << MAX_PHYSMEM_BITS, NULL,
				   ehca_create_busmap_callback);
	return ret;
}