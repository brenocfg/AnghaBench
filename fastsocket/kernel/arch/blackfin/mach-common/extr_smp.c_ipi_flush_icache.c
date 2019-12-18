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
struct blackfin_flush_data {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackfin_dcache_invalidate_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  blackfin_icache_flush_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipi_flush_icache(void *info)
{
	struct blackfin_flush_data *fdata = info;

	/* Invalidate the memory holding the bounds of the flushed region. */
	blackfin_dcache_invalidate_range((unsigned long)fdata,
					 (unsigned long)fdata + sizeof(*fdata));

	blackfin_icache_flush_range(fdata->start, fdata->end);
}