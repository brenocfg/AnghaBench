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
struct resource {int start; } ;
struct pcmcia_align_data {int mask; int offset; } ;
typedef  int resource_size_t ;

/* Variables and functions */

__attribute__((used)) static void
pcmcia_common_align(void *align_data, struct resource *res,
			resource_size_t size, resource_size_t align)
{
	struct pcmcia_align_data *data = align_data;
	resource_size_t start;
	/*
	 * Ensure that we have the correct start address
	 */
	start = (res->start & ~data->mask) + data->offset;
	if (start < res->start)
		start += data->mask + 1;
	res->start = start;
}