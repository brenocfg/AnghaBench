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
typedef  int u64 ;
struct page {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct extent_buffer {int start; int len; } ;

/* Variables and functions */
 scalar_t__ PAGE_CACHE_SIZE ; 
 struct extent_buffer* find_extent_buffer (struct extent_io_tree*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int page_offset (struct page*) ; 

struct extent_buffer *find_eb_for_page(struct extent_io_tree *tree,
				       struct page *page, int max_walk)
{
	struct extent_buffer *eb;
	u64 start = page_offset(page);
	u64 target = start;
	u64 min_start;

	if (start < max_walk)
		min_start = 0;
	else
		min_start = start - max_walk;

	while (start >= min_start) {
		eb = find_extent_buffer(tree, start, 0);
		if (eb) {
			/*
			 * we found an extent buffer and it contains our page
			 * horray!
			 */
			if (eb->start <= target &&
			    eb->start + eb->len > target)
				return eb;

			/* we found an extent buffer that wasn't for us */
			free_extent_buffer(eb);
			return NULL;
		}
		if (start == 0)
			break;
		start -= PAGE_CACHE_SIZE;
	}
	return NULL;
}