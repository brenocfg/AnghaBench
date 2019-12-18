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
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycle_t ;

/* Variables and functions */
 unsigned long L1_CACHE_BYTES ; 
 unsigned long PAGE_SIZE ; 
 unsigned long UVH_RTC ; 
 unsigned long uv_blade_processor_id () ; 
 int uv_get_min_hub_revision_id () ; 
 int /*<<< orphan*/  uv_read_local_mmr (unsigned long) ; 

__attribute__((used)) static cycle_t uv_read_rtc(struct clocksource *cs)
{
	unsigned long offset;

	if (uv_get_min_hub_revision_id() == 1)
		offset = 0;
	else
		offset = (uv_blade_processor_id() * L1_CACHE_BYTES) % PAGE_SIZE;

	return (cycle_t)uv_read_local_mmr(UVH_RTC | offset);
}