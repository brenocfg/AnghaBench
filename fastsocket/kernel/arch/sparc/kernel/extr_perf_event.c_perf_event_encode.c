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
struct perf_event_map {unsigned long pic_mask; scalar_t__ encoding; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long perf_event_encode(const struct perf_event_map *pmap)
{
	return ((unsigned long) pmap->encoding << 16) | pmap->pic_mask;
}