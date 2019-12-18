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
struct TYPE_2__ {unsigned int page_count; scalar_t__* virtual; } ;
struct vino_framebuffer {TYPE_1__ desc_table; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 

__attribute__((used)) static void vino_convert_to_rgba(struct vino_framebuffer *fb) {
	unsigned char *pageptr;
	unsigned int page, i;
	unsigned char a;

	for (page = 0; page < fb->desc_table.page_count; page++) {
		pageptr = (unsigned char *)fb->desc_table.virtual[page];

		for (i = 0; i < PAGE_SIZE; i += 4) {
			a = pageptr[0];
			pageptr[0] = pageptr[3];
			pageptr[1] = pageptr[2];
			pageptr[2] = pageptr[1];
			pageptr[3] = a;
			pageptr += 4;
		}
	}
}