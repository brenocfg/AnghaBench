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
struct ablkcipher_walk {scalar_t__ num; struct scatterlist* cache; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_SCATTERLIST_CACHE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ablkcipher_walk_init(struct ablkcipher_walk *w,
		int num, gfp_t gfp_flags)
{
	int i;

	num = min(ASYNC_SCATTERLIST_CACHE, num);
	sg_init_table(w->cache, num);

	w->num = 0;
	for (i=0; i<num; ++i) {
		struct page *page = alloc_page(gfp_flags);
		struct scatterlist *s;

		if (!page)
			break;

		s = &w->cache[i];

		sg_set_page(s, page, PAGE_SIZE, 0);
		w->num++;
	}

	return i;
}