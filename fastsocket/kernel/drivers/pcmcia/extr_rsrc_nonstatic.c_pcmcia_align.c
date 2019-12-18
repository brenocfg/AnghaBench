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
struct resource_map {unsigned long base; int num; struct resource_map* next; } ;
struct resource {unsigned long start; unsigned long end; } ;
struct pcmcia_align_data {struct resource_map* map; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_common_align (struct pcmcia_align_data*,struct resource*,int,int) ; 

__attribute__((used)) static void
pcmcia_align(void *align_data, struct resource *res, resource_size_t size,
		resource_size_t align)
{
	struct pcmcia_align_data *data = align_data;
	struct resource_map *m;

	pcmcia_common_align(data, res, size, align);

	for (m = data->map->next; m != data->map; m = m->next) {
		unsigned long start = m->base;
		unsigned long end = m->base + m->num - 1;

		/*
		 * If the lower resources are not available, try aligning
		 * to this entry of the resource database to see if it'll
		 * fit here.
		 */
		if (res->start < start) {
			res->start = start;
			pcmcia_common_align(data, res, size, align);
		}

		/*
		 * If we're above the area which was passed in, there's
		 * no point proceeding.
		 */
		if (res->start >= res->end)
			break;

		if ((res->start + size - 1) <= end)
			break;
	}

	/*
	 * If we failed to find something suitable, ensure we fail.
	 */
	if (m == data->map)
		res->start = res->end;
}