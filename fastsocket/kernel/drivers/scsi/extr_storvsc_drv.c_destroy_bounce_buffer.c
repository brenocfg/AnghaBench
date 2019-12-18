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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 

__attribute__((used)) static void destroy_bounce_buffer(struct scatterlist *sgl,
				  unsigned int sg_count)
{
	int i;
	struct page *page_buf;

	for (i = 0; i < sg_count; i++) {
		page_buf = sg_page((&sgl[i]));
		if (page_buf != NULL)
			__free_page(page_buf);
	}

	kfree(sgl);
}