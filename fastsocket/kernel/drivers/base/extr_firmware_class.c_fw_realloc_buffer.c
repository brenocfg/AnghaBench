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
struct firmware_priv {int page_array_size; int nr_pages; struct page** pages; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_HIGHMEM ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  fw_load_abort (struct firmware_priv*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (struct page**,struct page**,int) ; 
 int /*<<< orphan*/  memset (struct page**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fw_realloc_buffer(struct firmware_priv *fw_priv, int min_size)
{
	int pages_needed = ALIGN(min_size, PAGE_SIZE) >> PAGE_SHIFT;

	/* If the array of pages is too small, grow it... */
	if (fw_priv->page_array_size < pages_needed) {
		int new_array_size = max(pages_needed,
					 fw_priv->page_array_size * 2);
		struct page **new_pages;

		new_pages = kmalloc(new_array_size * sizeof(void *),
				    GFP_KERNEL);
		if (!new_pages) {
			fw_load_abort(fw_priv);
			return -ENOMEM;
		}
		memcpy(new_pages, fw_priv->pages,
		       fw_priv->page_array_size * sizeof(void *));
		memset(&new_pages[fw_priv->page_array_size], 0, sizeof(void *) *
		       (new_array_size - fw_priv->page_array_size));
		kfree(fw_priv->pages);
		fw_priv->pages = new_pages;
		fw_priv->page_array_size = new_array_size;
	}

	while (fw_priv->nr_pages < pages_needed) {
		fw_priv->pages[fw_priv->nr_pages] =
			alloc_page(GFP_KERNEL | __GFP_HIGHMEM);

		if (!fw_priv->pages[fw_priv->nr_pages]) {
			fw_load_abort(fw_priv);
			return -ENOMEM;
		}
		fw_priv->nr_pages++;
	}
	return 0;
}