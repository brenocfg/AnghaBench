#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mem_bswap_64 (void*,int) ; 

__attribute__((used)) static void swap_sample_id_all(union perf_event *event, void *data)
{
	void *end = (void *) event + event->header.size;
	int size = end - data;

	BUG_ON(size % sizeof(u64));
	mem_bswap_64(data, size);
}