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
struct page {int dummy; } ;
struct bitmap_storage {scalar_t__ file_pages; struct page** filemap; } ;

/* Variables and functions */
 size_t file_page_index (struct bitmap_storage*,unsigned long) ; 

__attribute__((used)) static inline struct page *filemap_get_page(struct bitmap_storage *store,
					    unsigned long chunk)
{
	if (file_page_index(store, chunk) >= store->file_pages)
		return NULL;
	return store->filemap[file_page_index(store, chunk)
			      - file_page_index(store, 0)];
}