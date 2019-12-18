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
struct kimage {int /*<<< orphan*/  unuseable_pages; int /*<<< orphan*/  dest_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kimage_free_page_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kimage_free_extra_pages(struct kimage *image)
{
	/* Walk through and free any extra destination pages I may have */
	kimage_free_page_list(&image->dest_pages);

	/* Walk through and free any unuseable pages I have cached */
	kimage_free_page_list(&image->unuseable_pages);

}